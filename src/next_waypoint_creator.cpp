#include "nav_manager/next_waypoint_creator.h"

NextWaypointCreator::NextWaypointCreator():private_nh("~")
{
    //parameter
    private_nh.param("hz",hz,{10});
    private_nh.param("border_distance",border_distance,{2.0});
    //subscriber
    sub_global_path = nh.subscribe("/global_path/path",10,&NextWaypointCreator::global_path_callback,this);
    sub_current_pose = nh.subscribe("/ekf_pose",10,&NextWaypointCreator::current_pose_callback,this);
    // sub_path = nh.subscribe("/global_path/path",10,&NextWaypointCreator::path_callback,this);

    //publisher
    pub_local_goal = nh.advertise<geometry_msgs::PoseStamped>("/next_waypoint",1);
    // pub_estimated_edge = nh.advertise<amsl_navigation_msgs::Edge>("/estimated_pose/edge", 1);
}

// void NextWaypointCreator::path_callback(const std_msgs::Int32MultiArray::ConstPtr& msg_path)
// {
//     std::cout<<"path callback "<<std::endl;
//     global_path_num = *msg_path;
//     have_recieved_multi_array = true;
// }
void NextWaypointCreator::global_path_callback(const nav_msgs::Path::ConstPtr& msg)
{
    std::cout<<"global_path callback "<<std::endl;
    global_path=*msg;
    std::cout<<"global_path size: " << global_path.poses.size() << std::endl;
    goal_number = 0;
    local_goal = global_path.poses[goal_number]; // goal_number番目の位置
    have_recieved_path = true;
}
void NextWaypointCreator::current_pose_callback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    std::cout<<"current_pose callback "<<std::endl;
    current_pose = *msg;
    // if(!have_recieved_pose) 
    have_recieved_pose = true;
}
void NextWaypointCreator::select_next_goal()
{
    double measure_distance = sqrt(pow(local_goal.pose.position.x-current_pose.pose.position.x,2)+pow(local_goal.pose.position.y-current_pose.pose.position.y,2)); // 自分の位置と次の通過ポイントの距離
    std::cout<<"distance: "<< measure_distance<<std::endl;
    if(measure_distance < border_distance) goal_number += 1;
    if(global_path.poses.size() > goal_number) local_goal = global_path.poses[goal_number];
    else local_goal = global_path.poses[global_path.poses.size()-1];
    if(goal_number == 0) goal_number ++;
    std::cout<<"goal_number: "<< goal_number <<std::endl;
    estimated_edge.node0_id = global_path_num.data[goal_number-1]; // 最後に通過したnode
    estimated_edge.node1_id = global_path_num.data[goal_number];
    std::cout<<"estimated_edge.node0: "<< estimated_edge.node0_id << " node1: " << estimated_edge.node1_id <<std::endl;
    pub_estimated_edge.publish(estimated_edge);
 }

void NextWaypointCreator::process()
{
    ros::Rate loop_rate(hz);
    while(ros::ok())
    {
        if(have_recieved_path && have_recieved_multi_array )
        {
            select_next_goal();
            local_goal.header.frame_id = "map";
            std::cout<<"local_goal :"<<local_goal.pose.position.x<<","<<local_goal.pose.position.y<<std::endl;
            pub_local_goal.publish(local_goal);
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
}

int main (int argc,char **argv)
{
    ros::init(argc, argv, "local_goal_creator");
    NextWaypointCreator local_goal_creator;
    local_goal_creator.process();
    return 0;
}
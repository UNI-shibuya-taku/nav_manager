#include "nav_manager/global_path_creator.h"
#include "nav_manager/waypoints.h"

GlobalPathCreator::GlobalPathCreator() :
	private_nh_("~")
    // ,
	// has_received_odom_(false), has_received_imu_(false), has_received_ndt_pose_(false),
	// is_first_(true), is_respawn_(false)
{
	// private_nh_.param("respawn_pose_topic_name",respawn_pose_topic_name_,{"/position/respawn"});
	// private_nh_.param("MOTION_NOISE_OO",MOTION_NOISE_OO_,{1e-3});

	// ndt_pose_sub_ = nh_.subscribe(ndt_pose_topic_name_,10,&EKF::ndt_pose_callback,this);
    pub_path = n.advertise<nav_msgs::Path>("/global_path/path_path",1);
    std::cout << "set global_path_creator!!!!" << std::endl;

    load_waypoints();
    load_route();
}
void GlobalPathCreator::load_waypoints()
{
    std::cout << "load_waypoints" << std::endl;
    if(!private_nh_.getParam("waypoints_list",waypoints_list_)){
        ROS_WARN("Cloud not load waypoints list");
        return;
    }
    ROS_ASSERT(waypoints_list_.getType() == XmlRpc::XmlRpcValue::TypeArray);
    std::cout << "finished ROS_ASSERT" << std::endl;
    std::cout << "waypoints_size: " << waypoints_list_.size() << std::endl;
    for(int i = 0; i < (int)waypoints_list_.size(); i++){
        std::cout << "i: " << i << std::endl;
        if(!waypoints_list_[i]["id"].valid() || !waypoints_list_[i]["x"].valid() || !waypoints_list_[i]["y"].valid()){
            ROS_WARN("waypoints list is valid");
            return;
        }
        std::cout << "clear ROS_WARN" << std::endl;
        if(waypoints_list_[i]["id"].getType() == XmlRpc::XmlRpcValue::TypeInt && waypoints_list_[i]["x"].getType() == XmlRpc::XmlRpcValue::TypeDouble && waypoints_list_[i]["y"].getType() == XmlRpc::XmlRpcValue::TypeDouble){
            std::cout << "the waypoint: " << waypoints_list_[i] << std::endl;
            int id = static_cast<int>(waypoints_list_[i]["id"]);
            double x = static_cast<double>(waypoints_list_[i]["x"]);
            double y = static_cast<double>(waypoints_list_[i]["y"]);
            std::cout << "id: " << id << " x: " << x << " y: " << y << std::endl;
            Waypoint waypoint(id, x, y);
            waypoints_.push_back(waypoint);
        }
    }
}
void GlobalPathCreator::load_route()
{
    std::cout << "load_route" << std::endl;
    if(!private_nh_.getParam("route_list",route_list_)){
        ROS_WARN("Cloud not load route list");
        return;
    }
    ROS_ASSERT(route_list_.getType() == XmlRpc::XmlRpcValue::TypeArray);
    std::cout << "finished ROS_ASSERT" << std::endl;
    for(int i = 0; i < (int)route_list_.size(); i++){
        if(!route_list_[i]["id"].valid()){
            ROS_WARN("route list is valid");
            return;
        }
        if(route_list_[i]["id"].getType() == XmlRpc::XmlRpcValue::TypeInt){
            int id = static_cast<int>(route_list_[i]["id"]);
            std::cout << "route_liset_: " << id << std::endl;
            routes_.push_back(id);
        }
    }
}

void GlobalPathCreator::process()
{
    while(ros::ok()){
        ros::spinOnce();
    }
}
int main (int argc, char **argv)
{
  ros::init(argc,argv,"global_path_creator");
  GlobalPathCreator global_path_creator;
  global_path_creator.process();
  return 0;
}
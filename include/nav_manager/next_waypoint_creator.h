#ifndef __NEXT_WAYPOINT_CREATOR_H
#define __NEXT_WAYPOINT_CREATOR_H
#include "ros/ros.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/PoseStamped.h"
#include <std_msgs/Int32MultiArray.h>
class NextWaypointCreator
{
public:
    NextWaypointCreator();
    void process();

private:
    //method
    void global_path_callback(const nav_msgs::Path::ConstPtr&);
    void current_pose_callback(const geometry_msgs::PoseStamped::ConstPtr&);
    void path_callback(const std_msgs::Int32MultiArray::ConstPtr&);
    void select_next_goal();
    //parameter
    int hz;
    double border_distance;

    //member
    ros::NodeHandle nh;
    ros::NodeHandle private_nh;
    ros::Publisher pub_local_goal;
    // ros::Publisher pub_estimated_edge;
    ros::Subscriber sub_global_path;
    ros::Subscriber sub_current_pose;
    // ros::Subscriber sub_path;

    nav_msgs::Path global_path;
    geometry_msgs::PoseStamped current_pose;
    geometry_msgs::PoseStamped local_goal;
    std_msgs::Int32MultiArray global_path_num;
    amsl_navigation_msgs::Edge estimated_edge;
    unsigned int goal_number;
    bool have_recieved_path = false;
    bool have_recieved_multi_array = false;
    bool have_recieved_pose = false;
};

#endif
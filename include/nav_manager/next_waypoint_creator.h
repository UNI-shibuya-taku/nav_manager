#ifndef __NEXT_WAYPOINT_CREATOR_H
#define __NEXT_WAYPOINT_CREATOR_H
#include "ros/ros.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/PoseStamped.h"
#include <std_msgs/Int32MultiArray.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>
#include <std_msgs/Bool.h>
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
    void load_task();
    //parameter
    int hz;
    double border_distance;

    //member
    ros::NodeHandle nh;
    ros::NodeHandle private_nh;

    ros::Subscriber sub_global_path;
    ros::Subscriber sub_current_pose;

    ros::Publisher pub_next_waypoint;
    ros::Publisher pub_task;

    nav_msgs::Path global_path;
    geometry_msgs::PoseStamped current_pose;
    geometry_msgs::PoseStamped next_waypoint;
    std_msgs::Int32MultiArray global_path_num;
    tf2_ros::TransformBroadcaster dynamic_br_;
    std_msgs::Bool is_whiteline_detector;
    unsigned int goal_number;
    bool have_recieved_path = false;
    bool have_recieved_multi_array = false;
    bool have_recieved_pose = false;
    XmlRpc::XmlRpcValue task_list_;
};

#endif

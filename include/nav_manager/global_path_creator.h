#ifndef __GLOBAL_PATH_CREATOR_H
#define __GLOBAL_PATH_CREATOR_H

// 受け取った順番に線を引く
#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "geometry_msgs/Pose2D.h"
#include "nav_msgs/Path.h"
#include "geometry_msgs/PointStamped.h"
#include <std_msgs/Int32MultiArray.h>
#include <amsl_navigation_msgs/Node.h>
#include <amsl_navigation_msgs/Edge.h>
#include <amsl_navigation_msgs/NodeEdgeMap.h>
#include <amsl_navigation_msgs/Replan.h>
class GlobalPathCreator
{
public:
    GlobalPathCreator();
    void process();

private:
    // void map_callback(const nav_msgs::OccupancyGrid::ConstPtr&);
    // void path_callback(const std_msgs::Int32MultiArray::ConstPtr&);
    // void node_edge_map_callback(const amsl_navigation_msgs::NodeEdgeMapConstPtr&);
    // void make_global_path();

    bool replan_flag;
    bool node_edge_flag;
    bool global_path_flag;
    ros::NodeHandle n;
    ros::NodeHandle private_n;
  
    ros::Publisher pub_path;
    ros::Publisher pub_open_grid;
    ros::Subscriber sub_map;
    ros::Subscriber sub_path;
    ros::Subscriber node_edge_map_sub;
    ros::Subscriber check_point_sub;

    nav_msgs::Path global_path;
    nav_msgs::Path waypoint_path;
    amsl_navigation_msgs::NodeEdgeMap map;
    std_msgs::Int32MultiArray check_points;
    std_msgs::Int32MultiArray global_path_num;
};


#endif// __SIMPLE_LOCALMAP_CREATOR_H

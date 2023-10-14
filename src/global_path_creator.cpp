#include "nav_manager/global_path_creator.h"
GlobalPathCreator::GlobalPathCreator() :
	private_nh_("~"),
	has_received_odom_(false), has_received_imu_(false), has_received_ndt_pose_(false),
	is_first_(true), is_respawn_(false)
{
	private_nh_.param("respawn_pose_topic_name",respawn_pose_topic_name_,{"/position/respawn"});
	private_nh_.param("MOTION_NOISE_OO",MOTION_NOISE_OO_,{1e-3});

	// ndt_pose_sub_ = nh_.subscribe(ndt_pose_topic_name_,10,&EKF::ndt_pose_callback,this);
    pub_path = n.advertise<nav_msgs::Path>("/global_path/path_path",1);

	// broadcaster_.reset(new tf2_ros::TransformBroadcaster);
	// buffer_.reset(new tf2_ros::Buffer);
	// listener_.reset(new tf2_ros::TransformListener(*buffer_));

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
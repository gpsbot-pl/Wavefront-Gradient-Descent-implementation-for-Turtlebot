#include <ros/ros.h>

#include "wavefront.hpp"

int main( int argc, char** argv ){
  
  ros::init( argc, argv, "wavefront" );
  ros::NodeHandle nh;

  ros::Subscriber sub_goal = nh.subscribe( "/move_base_simple/goal", 
					   1,
					   callback_wavefront_goal );

  ros::spin();

  return 0;

}

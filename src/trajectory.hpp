
#ifndef __TRAJECTORY_HPP__
#define __TRAJECTORY_HPP__

#include <geometry_msgs/PoseStamped.h>

// This function is called everytime the a new position goal is given
void callback_robot_goal( const geometry_msgs::PoseStamped& goal );


void
compute_robot_velocity
( double& linear_velocity, double& angular_velocity,
  double x_goal, double y_goal, 
  double x_current, double y_current, double theta_current );

#endif

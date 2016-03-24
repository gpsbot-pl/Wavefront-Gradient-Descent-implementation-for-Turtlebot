#include "trajectory.hpp"

// The global position list used to move the robot to a new position
std::list< geometry_msgs::Pose > robot_goal_positions;

// The robot goal callback that queues goal positions
void callback_robot_goal( const geometry_msgs::PoseStamped& goal )
{ robot_goal_positions.push_back( goal.pose ); }


void
compute_robot_velocity
( double& linear_velocity, double& angular_velocity,
  double x_goal, double y_goal, 
  double x_current, double y_current, double theta_current ){

  double delta_x = x_goal - x_current;
  double delta_y = y_goal - y_current;

  double theta_goal = atan2( delta_y, delta_x );

  linear_velocity = 0.0;
  angular_velocity = 0.0;

  double angle_error = atan2( sin( theta_goal - theta_current ),
			      cos( theta_goal - theta_current ) );

  if( 0.01 < fabs( angle_error ) ){
    angular_velocity = angle_error;
    return;
  }

  if( 0.001 < sqrt( (x_goal-x_current)*(x_goal-x_current) +
		    (y_goal-y_current)*(y_goal-y_current) ) ){
    linear_velocity = 0.05;
    return;
  }

}

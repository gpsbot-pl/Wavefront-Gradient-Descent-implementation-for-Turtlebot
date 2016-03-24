#include <ros/ros.h>

#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>

#include <geometry_msgs/Twist.h>

#include "gradient_descent.hpp"
#include "trajectory.hpp"

int main( int argc, char** argv ){
  
  ros::init( argc, argv, "trajectory" );
  ros::NodeHandle nh;

  // This is the list of robot goal positions (defined elsewhere)
  extern std::list< geometry_msgs::Pose > robot_goal_positions;

  // This node subscribe to the following topic to get position goals
  ros::Subscriber sub_goal = nh.subscribe( "/move_base_simple/goal", 
					   1,
					   callback_simulation );

  ros::Publisher pub_twist;
  pub_twist=nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);

  // To listen to the current position and orientation of the robot
  // wiki.ros.org/tf/Tutorials/Writing%20a%20tf%20listener%20%28C%2B%2B%29
  tf::TransformListener listener;

  // Rate (Hz) of the trajectory
  // http://wiki.ros.org/roscpp/Overview/Time
  ros::Rate rate( 100 );            // the trajectory rate
  double period = 1.0/100.0;        // the period

  bool readinitpose = true;         // used to initialize setpoint
  bool wait_for_robot = false;      // indicates that the robot is moving
  tf::Transform goal;               // the destination setpoint    

  // This is the main trajectory loop
  // At each iteration it computes and publishes a new joint positions that
  // animate the motion of the robot
  // The loop exits when CTRL-C is pressed.
  while( nh.ok() ){

    // Read the current forward kinematics of the robot
    // wiki.ros.org/tf/Tutorials/Writing%20a%20tf%20listener%20%28C%2B%2B%29
    tf::StampedTransform current;
    try{

      // TODO
      // Change the name of the reference frame and target frame.
      // These names will be used by tf to return the position/orientation of
      // the last link of the robot with respect to the base of the robot
      std::string target_frame( "odom" );
      std::string source_frame( "base_footprint" );

      listener.lookupTransform( target_frame, 
				source_frame, 
				ros::Time(0), 
				current );

      // This if is used to initialize the position (a small hack)
      if( readinitpose ){
	goal = current;
	readinitpose = false;
      }
    }

    catch(tf::TransformException ex)
      { std::cout << ex.what() << std::endl; }

    // If the list is not empty, 
    // Read a setpoint from the list and keep the translation
    if( !robot_goal_positions.empty() && !wait_for_robot ){
      tf::poseMsgToTF( robot_goal_positions.front(), goal );
      robot_goal_positions.pop_front();
    }
    
    tf::Transform error = current.inverse() * goal;
    if( 0.01 < error.getOrigin().length()  ){
      wait_for_robot = true;

      // Determine a desired cartesian linear velocity. 
      // We will command the robot to move with this velocity
      geometry_msgs::Twist twist;

      double current_theta = ( current.getRotation().getAngle()*
			       current.getRotation().getAxis().getZ() );
      current_theta = atan2( sin(current_theta), cos(current_theta) );

      compute_robot_velocity( twist.linear.x, twist.angular.z, 
			      goal.getOrigin().getX(),
			      goal.getOrigin().getY(),
			      current.getOrigin().getX(),
			      current.getOrigin().getY(),
			      current_theta );
      
      pub_twist.publish( twist );

    }
    else{
      wait_for_robot = false;
    }

    // 
    ros::spinOnce();

    // sleep
    rate.sleep();

  }

  return 0;

}

#include "wavefront.hpp"
#include "trajectory.hpp"

/**
 *
 * TODO
 *
 * Implement a "one-step" gradient descent. Given the distance_map and the 
 * current_row and current_col position of the robot, find the neighbor 
 * (i.e. (current_row-1,current_col), (current_row+1,current_col), 
 * (current_row,current_col-1) and (current_row,current_col+1)) with the 
 * the closest to the goal and return its row index and column index.
 * 
 * next_row (output): The row index of the neighbor closest to the goal
 * next_col (output): The column index of the neighbor closest to the goal
 * distance_map (input): The map that contains all the distances to the goal
 * current_row (input): The row index corresponding to the current position of 
 *                      the robot
 * current_row (input): The column index corresponding to the current position
 *                      of the robot
 */ 
void gradient_descent_step( int& next_row, int& next_col,
			    unsigned char distance_map[MAP_HEIGHT][MAP_WIDTH],
			    int current_row, int current_col ){

  // TODO
int z=-1+distance_map[current_row][current_col];//search for next position (one less than current value
next_row=current_row;
next_col=current_col;
if( distance_map[-1+current_row][current_col]==z)
{next_row=-1+current_row;}  //if this location has that z value then move there
else if( distance_map[current_row][-1+current_col]==z)
{next_col=-1+current_col;}
else if( distance_map[1+current_row][current_col]==z)
{next_row=1+current_row;}
else
{next_col= 1+current_col;}
}


// These are the initial row/column position of the robot
static int current_row = MAP_HEIGHT/2;
static int current_col = MAP_WIDTH/2;

/**
 *
 * DO NOT TOUCH THIS FUNCTION
 * 
 * This method calls the wave-front planner each time a goal message is
 * received. Then it finds the path using gradient descent.
 *
 */
void callback_simulation( const geometry_msgs::PoseStamped& msg_goal ){

  Coordinates goal;

  // Rows correspond to y coordinates
  // Columns correspond to x coordinates
  goal.row = -msg_goal.pose.position.y+(MAP_HEIGHT/2); 
  goal.col = msg_goal.pose.position.x+(MAP_WIDTH/2);

  // Access to the clean map
  extern unsigned char map[MAP_HEIGHT][MAP_WIDTH];

  // Create and initialize the map
  unsigned char distance_map[MAP_HEIGHT][MAP_WIDTH];
  memcpy( distance_map, map, MAP_HEIGHT*MAP_WIDTH*sizeof(unsigned char) );
  distance_map[goal.row][goal.col] = 2;

  // call wave-front and print the map
  wave_front( distance_map, goal );
  print_map( distance_map );

  // While we're not at the goal
  while( distance_map[current_row][current_col] != 2 ){

    // do a gradient descent step
    gradient_descent_step( current_row, current_col,
			   distance_map,
			   current_row, current_col );

    // convert to 3D coordinates and queue the result
    geometry_msgs::PoseStamped pose;
    pose.pose.position.y = -current_row + MAP_HEIGHT/2;
    pose.pose.position.x = current_col - MAP_WIDTH/2;
    callback_robot_goal( pose );
  }

}

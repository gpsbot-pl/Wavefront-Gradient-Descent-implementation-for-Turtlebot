
#ifndef __WAVEFRONT_HPP__
#define __WAVEFRONT_HPP__

#include <geometry_msgs/PoseStamped.h>

// Default map size
// DO NOT TOUCH
#define MAP_HEIGHT 15
#define MAP_WIDTH  15

// Structure to represents map coordinates
struct Coordinates{ int row, col; };

/**
 * 
 * 
 * Compute the distance map using the wave-front algorithm. Each element of the 
 * distance map represents the remaining distance to the goal.
 * 
 * distance_map (input/output): The distance map. On input, the map is 
 *                              initialized with "0" for free-space squares, "1"
 *                              for obstacle squares and "2" for the goal 
 *                              square. On output all "0" are replaced by an 
 *                              integer representing the distance to the goal.
 * goal (input):                The coordinates of the goal.
 *
 */
void wave_front( unsigned char distance_map[MAP_HEIGHT][MAP_WIDTH],
		 const Coordinates& goal );

/**
 *
 * DO NOT TOUCH
 * 
 * Helper function to print the distance map to the screen
 * (helpful for debugging)
 * 
 */
void print_map( unsigned char distance_map[MAP_HEIGHT][MAP_WIDTH] );


/**
 * 
 * DO NOT TOUCH
 *
 * This method is calls the wavefront planner each time a goal message is
 * received.
 * 
 */
void callback_wavefront_goal( const geometry_msgs::PoseStamped& msg_goal );

#endif

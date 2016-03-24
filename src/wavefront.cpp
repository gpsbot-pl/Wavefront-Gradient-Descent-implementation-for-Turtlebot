#include "wavefront.hpp"
#include <list>
/**
 * 
 * DO NOT TOUch
  This is the default map. Each element indicates if the space is free or 
  occupied by an obstacle. A "1" indicates an obstacle.

  The coordinate system of the map is as follow and the origin of the coordinate
  system is in the center of the map (i.e. map[7][7]). The robot always starts
  from the center of the map.
  
  ^ Y
  |
  |
  -----> X
*/
unsigned char map[MAP_HEIGHT][MAP_WIDTH] = 
  { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1 },
    { 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
    { 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1 },
    { 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1 },
    { 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };

/**
 * Helper function to print the distance map to the screen
 * (helpful for debugging)
 */
void print_map( unsigned char distance_map[MAP_HEIGHT][MAP_WIDTH] ){

  for( int c=0; c<MAP_WIDTH; c++ ){
    std::cout << std::setw(5);
    if( c == MAP_WIDTH/2 )      { std::cout << "Y"; }
    else                        { std::cout << " "; }
  }
  std::cout << std::endl;
  for( int c=0; c<MAP_WIDTH; c++ ){
    std::cout << std::setw(5);
    if( c == MAP_WIDTH/2 )      { std::cout << "^"; }
    else                        { std::cout << " "; }
  }
  std::cout << std::endl;

  for( int r=0; r<MAP_HEIGHT; r++ ){
    for( int c=0; c<MAP_WIDTH; c++ ){
      std::cout << std::setw(5);
      if( r == MAP_HEIGHT/2 ) {
	if( 1 < distance_map[r][c] ) { std::cout << std::setfill('-') 
						 << (int)distance_map[r][c]; }
	else                         { std::cout << std::setfill('-') <<  "-"; }
	if( c == MAP_WIDTH-1 )
	  { std::cout << "> X"; }
      }
      else if( c == MAP_WIDTH/2 ) {
	if( 1 < distance_map[r][c] ) { std::cout << std::setfill(' ') 
						 << (int)distance_map[r][c]; }
	else                         { std::cout << std::setfill(' ') <<  "|"; }
      }
      else{
	if( 1 < distance_map[r][c] ) { std::cout << std::setfill(' ') 
						 << (int)distance_map[r][c]; }
	else                         { std::cout << std::setfill(' ') << " "; }
      }
    }
    std::cout << std::endl;
  }
}

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
int minim( int q, int r )//find minimum of two integers and return
{
  return( ( q<r )? q:r);
}

void wave_front( unsigned char distance_map[MAP_HEIGHT][MAP_WIDTH],
                 const Coordinates& goal ){

int i,j,m,n,temp1,temp2,temp3,temp4;
std::list<int> first; //to store row positions of zero locations
std::list<int> second;// to store column positions of zero locations
std::cout << " hi ";
for( i=1; i<MAP_HEIGHT; i++)  //loop over rows; ignore bounding box walls
  {
 for( j=1; j<MAP_WIDTH; j++)  //loop over coulmns; ignore bounding box walls
    {
    if( distance_map[i][j]==0)   //if value at location is 0 (not filled yet)
    {
     first.push_back(i);
     second.push_back(j);}}} // store location in list

std::list<int>::iterator it1;//list iterators
std::list<int>::iterator it2;

while(first.size()!=0 && second.size()!=0) // while some cells are still not filled
{
for(it1=first.begin(),it2=second.begin(); it1 != first.end() && it2 != second.end();)
{
    m= *it1;
    n= *it2;
      //find lowest filled neigbour that is not a wall
      if( distance_map[1+m][n]>1)
      {
       temp1= distance_map[1+m][n];}
      else
      {
      temp1= 50;} //very large number to make it inconsequential to minimum finding function
      if( distance_map[m][1+n]>1)
     {
       temp2= distance_map[m][1+n];}
     else
     {
       temp2= 50;}
      if( distance_map[-1+m][n]>1)
     {
temp3= distance_map[-1+m][n];}
      else
      {
       temp3= 50;}
    if( distance_map[m][-1+n]>1)
      {
       temp4= distance_map[m][-1+n];}
     else
       {
       temp4= 50;}
      if( (temp1==50) && (temp2==50) && (temp3==50) && (temp4==50) )
       {
      distance_map[m][n]=0;//All neighbours are walls/unfilled
      ++it1;
      ++it2;
       }
      else
       {
       distance_map[m][n]=1+(minim(minim(temp1,temp2),minim(temp3,temp4)));
       it1=first.erase(it1);
       it2=second.erase(it2);     }//remove filled location from list
}}}

/**
 * 
 *
 * This method calls the wavefront planner each time a goal message is
 * received and prints the output.
 * 
 */
void callback_wavefront_goal( const geometry_msgs::PoseStamped& msg_goal ){
  Coordinates goal;

  // Rows correspond to y coordinates
  // Columns correspond to x coordinates
  goal.row = -msg_goal.pose.position.y+(MAP_HEIGHT/2); 
  goal.col = msg_goal.pose.position.x+(MAP_WIDTH/2);

  // Create and initialize the map
  unsigned char distance_map[MAP_HEIGHT][MAP_WIDTH];
  memcpy( distance_map, map, MAP_HEIGHT*MAP_WIDTH*sizeof(unsigned char) );
  distance_map[goal.row][goal.col] = 2;

  // call wave-front and print the map
  wave_front( distance_map, goal );
  print_map( distance_map );

}


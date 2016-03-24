### Wavefront-Gradient-Descent-implementation-for-Turtlebot
This requires you to install Turtlebot package and other dependencies for ROS Hydro. <br />

The Rviz scene shows a 15x15 tile environment with a turtlebot right in the central tile. <br />

The wavefront planner computes the shortest path from each tile to a specified goal position. <br />
Each free square is represented by a “0”, obstacles are represented by a “1” and the goal <br />
position will be represented by a “2”.<br />
Launch the wavefront planner using : roslaunch assignment2 turtlebot_wavefront.launch  <br />
Publish goal in a separate terminal like so: rosrun assignment2 publish_goal -6 6 <br />
<br />

The gradient descent algorithm uses the computed wavefront to send the turtlebot to the specified destination<br />
on the shortest path, while avoiding obstacles.<br />
Launch the simulator and planner together with:<br /> roslaunch assignment2 turtlebot_planner.launch <br />
Publish goal in a separate terminal like so: rosrun assignment2 publish_goal -6 6 <br />

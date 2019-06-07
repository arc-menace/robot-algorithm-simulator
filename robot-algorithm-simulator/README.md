TODO:
- Make separate files for the data collection of the map, block, obstacles and Robot data

The robot chooses an order in which to go after the blocks and then a path to the first block. 
When the robot is going to move in a certain direction, its path is a rectangle (width of robot 
by length of path plus the length of the robot). Program will check whether any blocks are 
contained in that rectangle and will stop the robot 1 sensing distance away from the block. The 
block's coordinates are added to the vector of blocks known to the robot. The robot then chooses
its next path or decides to pursue another block.

//Algorithm
Robot needs to be able to identify the mothership by noting a cluster of blocks.
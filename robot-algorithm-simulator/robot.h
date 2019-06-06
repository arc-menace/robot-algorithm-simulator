#pragma once
#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "rmas6219.h"

//Robot class
class Robot {
public:

	//Default position in the bottom left corner of the map (0,0)
	Robot(double current_x = DEFAULT_START, double current_y = DEFAULT_START);

	std::vector<Obstacle> known_obstacles; //Robot Only knows the locations of obstacles which have come within its sensing distance.

	void rotate_cw(double num_degrees); //Rotate Clockwise
	void rotate_ccw(double num_degrees); //Rotate Counter-Clockwise
	void forward(double num_inches); // Move Forward
	void backward(double num_inches); //Move Backward

	//Where the Robot is and where it is going
	double x = 48; //Full map is 96" square. (48,48) is center
	double y = 48;
	double next_x = 0;
	double next_y = 0;

	//Robot must remember where it started to return there at the end
	double starting_x = 48;
	double starting_y = 48;

	//Size of the robot in inches
	float width = 12;
	float length = 12;

	//Distance away from an obstacle before the robot senses its presence
	double sensing_distance = 1;

	double wheel_diameter = 4.0; //In inches.

	double orientation = 90; //Direction the Robot is pointing is measured in degrees.
	//0 = East, 90 = North, 180 = West and 270 = South
};


#endif ROBOT_H
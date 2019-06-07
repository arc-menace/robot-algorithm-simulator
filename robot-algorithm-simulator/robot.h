#pragma once
#ifndef ROBOT_H
#define ROBOT_H

#include "rmas6219.h"
#include <vector>

//Robot class
class Robot {
public:

	//Default position in the bottom left corner of the map (0,0)
	Robot(double current_x, double current_y) { //Unknown parameter change issue when constructor
		x = current_x;															//is placed in the .cpp file.
		y = current_y;
		starting_x = x;
		starting_y = y;
	}

	void rotate_cw(double num_degrees) { //Rotate Clockwise
		orientation -= num_degrees;
		if (orientation < 0) {
			orientation += 360; //Converts a negative number of degrees to positive 
								//(Ex. -40 degrees = 320 degrees = -40 degrees + 360 degrees)
		}
	}

	void rotate_ccw(double num_degrees) { //Rotate CounterClockwise
		orientation += num_degrees;
		if (orientation >= 360) {
			orientation -= 360; //Converts a number of degrees >= 360 back between 0 and 360 
								//(Ex. 400 degrees = 40 degrees = 400 degrees - 360 degrees)
		}
	}

	void forward(double num_inches) { //X and Y are the adjacent and opposite sides of a triangle 
								   //with hypotenuse num_inches and theta orientation
		y += num_inches * sin(orientation);
		x += num_inches * cos(orientation);
	}

	void backward(double num_inches) { //Same math as forward movement except... backwards...
		y -= num_inches * sin(orientation);
		x -= num_inches * cos(orientation);
	}

	void set_orientation(double direction) { //Faces the robot whatever direction the user desires.
		orientation = direction; 
	}

	void set_sensing_distance(double sense_dist) {
		sensing_distance = sense_dist;
	}

	void set_wheel_diameter(double diameter) {
		wheel_diameter = diameter;
	}

	//Where the Robot is going
	double next_x = 0;
	double next_y = 0;

	//Robot must remember where it started to return there at the end
	double starting_x = 48;
	double starting_y = 48;

	//Size of the robot in inches
	float width = 12;
	float length = 12;

private:
	//Distance away from an obstacle before the robot senses its presence
	double sensing_distance = 1;

	double wheel_diameter = 4.0; //In inches.

	double orientation = 90; //Direction the Robot is pointing is measured in degrees.
							 //0 = East, 90 = North, 180 = West and 270 = South
	double x = 48; //Full map is 96" square. (48,48) is center
	double y = 48;
};


#endif ROBOT_H
#include "rmas6219.h"
#include <vector>

//Robot class
class Robot {
public:
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

	//Default position in the bottom left corner of the map (0,0)
	Robot(double current_x = DEFAULT_START, double current_y = DEFAULT_START) {
		x = current_x;
		y = current_y;
		starting_x = x;
		starting_y = y;
	}

	std::vector<Obstacle> known_obstacles;

	double orientation = 90; //Direction the Robot is pointing is measured in degrees.
								 //0 = East, 90 = North, 180 = West and 270 = South

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
	/*
	bool scan_envrnmt(std::vector<Obstacle> obstacles) {
		bool obstacle_close = false;
		for (int i = 0; i < obstacles.size(); i++) {
			if (obstacles[i].stated_x <= x + (width / 2) + sensing_distance) {
				known_obstacles.push_back(obstacles[i]);
				obstacle_close = true;
			}
		}
		return obstacle_close;
	}
	*/
};

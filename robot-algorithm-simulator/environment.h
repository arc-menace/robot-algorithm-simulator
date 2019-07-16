#pragma once
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <math.h>
#include "global.h"
#include "robot.h"
#include "block.h"
#include "obstacle.h"
//#include "map.h"
//#include "mothership.h"

namespace rmas {
	class Environment {
	/*
		Class controls all movement
		Moves Robot (log)
		Keeps track of obstacles and blocks on robot, map and mothership
		tracks collisions (log)
		tracks the robot falling off the map (log) (end of round)
		tracks blocks being picked up (log)
		tracks blocks being placed on the mothership (log)
		tracks the end of the round
		does all logging (indexed logging for replication)
	*/

	private:
		//vector of blocks
		//vector of obstacles
	public:
		//==============================================
		//	Robot Movement Functions
		//==============================================

		//All functions need to check for collisions in given path
		//if the robot collides with the mothership, the mothership does not move. The robot can get on top of the mothership
		//if the robot hits a block or an obstacle, the object is moved with the robot
		
		Robot robot;
		void set_orientation(double direction) { //Faces the robot whatever direction the user desires.
			while (direction >= 360.0) {
				direction -= 360; //Ex. set_orientation(720)
			}
			while (direction <= 0.0) {
				direction += 360.0; //Ex. set_orientation(-950)
			}
			if (direction < robot.orientation) {
				rotate_cw(robot.orientation - direction);
			}
			if (direction > robot.orientation) {
				rotate_ccw(direction - robot.orientation);
			}

		}

		void rotate_cw(double num_degrees) { //Rotate Clockwise
			robot.orientation -= num_degrees;
			if (robot.orientation < 0) {
				robot.orientation += 360; //Converts a negative number of degrees to positive 
									//(Ex. -40 degrees = 320 degrees = -40 degrees + 360 degrees)
			}
			std::string message = "Rotated Clockwise " + std::to_string(num_degrees) + ". Robot oriented at " + std::to_string(orientation);
		}

		void rotate_ccw(double num_degrees) { //Rotate CounterClockwise

			robot.orientation += num_degrees;
			if (robot.orientation >= 360) {
				robot.orientation -= 360; //Converts a number of degrees >= 360 back between 0 and 360 
									//(Ex. 400 degrees = 40 degrees = 400 degrees - 360 degrees)
			}
		}

		void forward(double num_inches) { //X and Y are the adjacent and opposite sides of a triangle 
										  //with hypotenuse num_inches and theta orientation
			robot.y += num_inches * sin(robot.orientation * convert_deg);
			robot.x += num_inches * cos(robot.orientation * convert_deg);
		}

		void backward(double num_inches) { //Same math as forward movement except... backwards...
			robot.y -= num_inches * sin(robot.orientation * convert_deg);
			robot.x -= num_inches * cos(robot.orientation * convert_deg);
		}

		void right(double num_inches) {
			if (robot.is_mechanum) {
				robot.x += num_inches * sin(robot.orientation * convert_deg);
				robot.y += num_inches * cos(robot.orientation * convert_deg);
			}
			else {
				rotate_cw(90);
				forward(num_inches);
				rotate_ccw(90);
			}
		}

		void left(double num_inches) {
			if (robot.is_mechanum) {
				robot.x -= num_inches * sin(robot.orientation * convert_deg);
				robot.y -= num_inches * cos(robot.orientation * convert_deg);
			}
			else {
				rotate_ccw(90);
				forward(num_inches);
				rotate_cw(90);
			}
		}

		/*
			Diagonal movement(mostly for mechanum) moves at 45 degree angle
		*/

		//void sense(){
		//return x,y
		//}

		//bool pickUp Block{
		//return true/false successful
		//}

		//==============================================
		//	Block Movement Functions
		//==============================================



		//==============================================
		//	Obstacle Movement Functions
		//==============================================




	};
}

#endif
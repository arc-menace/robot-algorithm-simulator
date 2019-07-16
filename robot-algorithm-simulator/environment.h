#pragma once
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <math.h>
#include <string>
#include "global.h"
#include "robot.h"
#include "block.h"
#include "obstacle.h"
#include "event.h"
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
		Robot robot;
		int index = 0;
		int round_num = 1;
		//map
		//vector of blocks
		//vector of obstacles

		//==============================================
		//	Block Generation Functions
		//==============================================

		//==============================================
		//	Block Movement Functions
		//==============================================

		//==============================================
		//	Obstacle Generation Functions
		//==============================================

		//==============================================
		//	Obstacle Movement Functions
		//==============================================


	public:
		Environment(Robot main_robot, int round_number = 0, bool rand_blocks = true, bool rand_obstacles = true) {
			robot = main_robot;
			round_num = round_number;
		}

		//==============================================
		//	Robot Movement Functions
		//==============================================

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
			Event::Move move(index, robot);
		}

		void rotate_cw(double num_degrees) { //Rotate Clockwise
			robot.orientation -= num_degrees;
			if (robot.orientation < 0) {
				robot.orientation += 360; //Converts a negative number of degrees to positive 
									//(Ex. -40 degrees = 320 degrees = -40 degrees + 360 degrees)
			}
			Event::Move move(index, robot);
		}

		void rotate_ccw(double num_degrees) { //Rotate CounterClockwise

			robot.orientation += num_degrees;
			if (robot.orientation >= 360) {
				robot.orientation -= 360; //Converts a number of degrees >= 360 back between 0 and 360 
									//(Ex. 400 degrees = 40 degrees = 400 degrees - 360 degrees)
			}
			Event::Move move(index, robot);
		}

		void forward(double num_inches) { //X and Y are the adjacent and opposite sides of a triangle 
										  //with hypotenuse num_inches and theta orientation
			robot.y += num_inches * sin(robot.orientation * convert_deg);
			robot.x += num_inches * cos(robot.orientation * convert_deg);
			Event::Move move(index, robot);
		}

		void backward(double num_inches) { //Same math as forward movement except... backwards...
			robot.y -= num_inches * sin(robot.orientation * convert_deg);
			robot.x -= num_inches * cos(robot.orientation * convert_deg);
			Event::Move move(index, robot);
		}

		void right(double num_inches) {
			if (robot.is_mechanum) {
				robot.x += num_inches * sin(robot.orientation * convert_deg);
				robot.y += num_inches * cos(robot.orientation * convert_deg);
				Event::Move move(index, robot);
			}
			else {
				rotate_cw(90);
				forward(num_inches);
				rotate_ccw(90);
				Event::Move move(index, robot);
			}
		}

		void left(double num_inches) {
			if (robot.is_mechanum) {
				robot.x -= num_inches * sin(robot.orientation * convert_deg);
				robot.y -= num_inches * cos(robot.orientation * convert_deg);
				Event::Move move(index, robot);
			}
			else {
				rotate_ccw(90);
				forward(num_inches);
				rotate_cw(90);
				Event::Move move(index, robot);

			}
		}

		/*
			Diagonal movement(mostly for mechanum) moves at 45 degree angle
		*/

		//void sense(){
		//return x,y
		//}

		//int signal end

		//private:
		//bool pickUp Block{
		//return true/false successful
		//}
	};
}

#endif
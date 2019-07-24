#pragma once
#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <iostream>
#include "block.h"
#include "obstacle.h"
#include "global.h"
#include "object.h"

namespace rmas {
	//Robot class
	class Robot {
	private:
		friend class Environment;
		//Robot must remember where it started to return there at the end
		double starting_x = DEFAULT_ROBOT_X;
		double starting_y = DEFAULT_ROBOT_Y;

		double x = starting_x; //Full map is 96" square. (48,48) is center
		double y = starting_y;

		bool is_mechanum = false;

		double orientation = DEFAULT_START_ORIENTATION; //Direction the Robot is pointing is measured in degrees.
								 //0 = East, 90 = North, 180 = West and 270 = South

		//Size of the robot in inches. Need to create function to utilize
		float width = DEFAULT_ROBOT_WIDTH;
		float length = DEFAULT_ROBOT_LENGTH;

		double sensing_distance = MAX_SENSE_DIST; //How far away the sensor can accurately sense
		double sensing_angle = 360.0; //How much of the circle around the robot is visible to the sensor(s)

		double wheel_diameter = 0; //In inches. Distance travelled/time elapsed is ignored by default so the diameter is 0

		std::vector<Block> blocks_on_robot;
		std::vector<Obstacle> known_obstacles;
		std::vector<Object> objects;

		Shape shape = Shape::SQUARE;
	public:
		void mechanum(bool change) {
			is_mechanum = change;
		}

		double return_width() {
			return width;
		}

		double return_length() {
			return length;
		}

		double return_x() {
			return x;
		}

		double return_y() {
			return y;
		}

		double return_orientation() {
			return orientation;
		}

		double return_sensing_distance() {
			return sensing_distance;
		}

		Shape return_shape() {
			return Shape::SQUARE;
		}
		
		double return_radius() {
			return 0;
		}

		void set_wheel_diameter(double diameter) {
			if (diameter > MAX_WHEEL_DIAM) {
				diameter = MAX_WHEEL_DIAM;
			}
			if (diameter < 0) {
				diameter = 0;
			}
			wheel_diameter = diameter;
		}

		void define_sensors(double distance, double angle) {
			if (distance > MAX_SENSE_DIST) {
				distance = MAX_SENSE_DIST;
			}
			if (distance < MIN_SENSE_DIST) {
				distance = MIN_SENSE_DIST;
			}
			while (angle >= 360.0) { //Keeps angle between 0 and 360
				angle -= 360.0;
			}
			while (angle < 0) { //See previous comment
				angle += 360.0;
			}
			sensing_distance = distance;
			sensing_angle = angle;
		}

		void set_start(double x, double y) {
			//X,Y points of robot indicate center point of robot. 
			//These if statements prevent the robot from starting hanging off of the board.
			if (x < 0.0 + (width / 2)) { //
				x = 0.0 + (width / 2);
			}
			if (y < 0.0 + (length / 2)) {
				y = 0.0 + (length / 2);
			}
			if (x > 96.0 - (width / 2)) {
				x = 96.0 - (width / 2);
			}
			if (y > 96.0 - (length / 2)) {
				y = 96.0 - (length / 2);
			}
			starting_x = x;
			starting_y = y;
		}

		void print_atts(bool advanced = false) {
			std::cout << "Starting (X,Y): (" << starting_x << "," << starting_y << ")" << std::endl;
			std::cout << "Current (X,Y): (" << x << "," << y << ")" << std::endl;
			std::cout << "Orientation: " << orientation << char(248) << std::endl;
			std::cout << "Robot width: " << width << " inches" << std::endl;
			std::cout << "Robot length: " << length << " inches" << std::endl;
			if (advanced) {
				std::cout << "Robot can sense obstacles " << sensing_distance << " inches away within " <<
					sensing_angle << char(248) << std::endl;
				std::cout << "Wheels are " << wheel_diameter << " inches in diameter" << std::endl;
				std::cout << "There are " << blocks_on_robot.size() << " blocks currently on the robot" << std::endl;
				std::string true_false = "false";
				if (is_mechanum) {
					true_false = "true";
				}
				std::cout << "Mechanum Drive: " << true_false << std::endl;
			}
			std::cout << std::endl;
		}
	};
}

#endif
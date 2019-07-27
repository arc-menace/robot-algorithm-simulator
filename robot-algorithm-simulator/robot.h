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
	class Robot : public Rectangle {
	private:
		friend class Environment;

		//Robot must remember where it started to return there at the end
		double starting_x = DEFAULT_ROBOT_X;
		double starting_y = DEFAULT_ROBOT_Y;

		bool is_mechanum = false;

		double sensing_distance = MAX_SENSE_DIST; //How far away the sensor can accurately sense
		double sensing_angle = 360.0; //How much of the circle around the robot is visible to the sensor(s)

		double wheel_diameter = 0; //In inches. Distance travelled/time elapsed is ignored by default so the diameter is 0

		std::vector<Block> blocks_on_robot;
		std::vector<Obstacle> known_obstacles;
		std::vector<Object> objects;

		Shape shape = Shape::RECTANGLE;

	public:
		Robot(bool i_is_mechanum = false, 
			double i_x = DEFAULT_ROBOT_X, 
			double i_y = DEFAULT_ROBOT_Y, 
			double i_width = DEFAULT_ROBOT_WIDTH, 
			double i_length = DEFAULT_ROBOT_LENGTH, 
			double i_orientation = DEFAULT_START_ORIENTATION, 
			double i_sensing_distance = MAX_SENSE_DIST, 
			double i_sense_angle = 360.0, 
			double i_wheel_diameter = 0):
			Rectangle(i_x, i_y, i_width, i_length, i_orientation, "Robot" ),
			starting_x(i_x), starting_y(i_y), is_mechanum(i_is_mechanum),
			sensing_distance(i_sensing_distance), sensing_angle(i_sense_angle),
			wheel_diameter(i_wheel_diameter) {}

		double return_sensing_distance() { return sensing_distance; }
	};
}

#endif
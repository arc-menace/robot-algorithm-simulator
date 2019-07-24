#pragma once
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <math.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include "global.h"
#include "robot.h"
#include "block.h"
#include "obstacle.h"
#include "event.h"
#include "log.h"
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
		std::vector<Block> blocks;
		//map
		//Mothership generation
		//vector of blocks
		std::vector<Obstacle> obstacles;
		
		//==============================================
		//	Block Generation Functions
		//==============================================
		void generate_blocks(int num_blocks) {
			srand(time(0));
			for (int i = 0; i < num_blocks; i++) {
				int rand_x = rand() % 84 + 6;
				int rand_y = rand() % 84 + 6;
				//Set max and min to be edges of map taking the size of the obstacle into account
				blocks.push_back(Block(rand_x, rand_y));
				block_creation_log.add_event(Event::Block_Created(i, blocks[i]));
			}
		}
		//==============================================
		//	Block Movement Functions
		//==============================================

		//==============================================
		//	Obstacle Generation Functions
		//==============================================

		//==============================================
		//	Obstacle Movement Functions
		//==============================================

		//==============================================
		//	Shape Intersection Function
		//==============================================
		template<typename S1, typename S2>
		bool intersect(S1 ref_obj, S2 object2) {
			bool intersects = false;
			double delta_x = ref_obj.return_x() - object2.return_x();
			double delta_y = ref_obj.return_y() - object2.return_y();
			double distance_away = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
			double ref_angle = atan(abs(delta_y) / abs(delta_x));
			double angle = ref_obj.return_orientation() - ref_angle;

			double internal_distance1 = 0;
			double diag_angle = atan(ref_obj.return_width() / ref_obj.return_length());
			if (ref_obj.return_shape() == Shape::SQUARE) {
				if (angle > diag_angle && angle < diag_angle + 90 || angle > diag_angle + 180 && angle < diag_angle + 270) {
					double internal_distance1 = cos(angle) * ref_obj.return_length() / 2;
				}
				else {
					double internal_distance1 = cos(angle) * ref_obj.return_width() / 2;
				}
			}
			if (ref_obj.return_shape() == Shape::CIRCLE) {
				internal_distance1 = ref_obj.return_radius();
			}
			//Add functionality for compound shapes

			double internal_distance2 = 0;
			angle += 180; // other object is going to use the inverse angle
			diag_angle = atan(object2.return_width() / object2.return_length());
			if (angle > diag_angle && angle < diag_angle + 90 || angle > diag_angle + 180 && angle < diag_angle + 270) {
				double internal_distance2 = cos(angle) * object2.return_length() / 2;
			}
			else {
				double internal_distance2 = cos(angle) * object2.return_width() / 2;
			}
			if (object2.return_shape() == Shape::CIRCLE) {
				internal_distance2 = object2.return_radius();
			}
			if (distance_away <= internal_distance1 + internal_distance2) {
				intersects = true;
			}
			return intersects;
		}

		template<typename S1, typename S2>
		bool encapsulate(S1 ref_obj, S2 object2) {
			bool encapsulates = false;
			double delta_x = ref_obj.return_x() - object2.return_x();
			double delta_y = ref_obj.return_y() - object2.return_y();
			double distance_away = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
			double ref_angle = atan(abs(delta_y) / abs(delta_x));
			double angle = ref_obj.return_orientation() - ref_angle;

			double internal_distance1 = 0;
			double diag_angle = atan(ref_obj.return_width() / ref_obj.return_length());
			if (ref_obj.return_shape() == Shape::SQUARE) {
				if (angle > diag_angle && angle < diag_angle + 90 || angle > diag_angle + 180 && angle < diag_angle + 270) {
					double internal_distance1 = cos(angle) * ref_obj.return_length() / 2;
				}
				else {
					double internal_distance1 = cos(angle) * ref_obj.return_width() / 2;
				}
			}
			if (ref_obj.return_shape() == Shape::CIRCLE) {
				internal_distance1 = ref_obj.return_radius();
			}
			//Add functionality for compound shapes

			double internal_distance2 = 0;
			angle += 180; // other object is going to use the inverse angle
			diag_angle = atan(object2.return_width() / object2.return_length());
			if (object2.return_shape() == Shape::SQUARE) {
				if (angle > diag_angle && angle < diag_angle + 90 || angle > diag_angle + 180 && angle < diag_angle + 270) {
					double internal_distance2 = cos(angle) * object2.return_length() / 2;
				}
				else {
					double internal_distance2 = cos(angle) * object2.return_width() / 2;
				}
			}
			if (object2.return_shape() == Shape::CIRCLE) {
				internal_distance2 = object2.return_radius();
			}
			if (distance_away <= internal_distance1 - internal_distance2) {
				encapsulates = true;
			}
			return encapsulates;
		}

	public:
		Log <Event::Move> move_log;
		Log <Event::Block_Created> block_creation_log;

		Environment(Robot main_robot, int num_blocks = 0, int num_obstacles = 0, bool rand_blocks = true, bool rand_obstacles = true) {
			robot = main_robot;
			move_log.add_event(Event::Move(index++, robot)); //Set initial poisition
			generate_blocks(num_blocks);
		}

		Block return_block(int ind) {
			return blocks[ind];
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
			move_log.add_event(Event::Move(index++, robot));
		}

		void rotate_cw(double num_degrees) { //Rotate Clockwise
			robot.orientation -= num_degrees;
			if (robot.orientation < 0) {
				robot.orientation += 360; //Converts a negative number of degrees to positive 
									//(Ex. -40 degrees = 320 degrees = -40 degrees + 360 degrees)
			}
			move_log.add_event(Event::Move(index++, robot));
		}

		void rotate_ccw(double num_degrees) { //Rotate CounterClockwise

			robot.orientation += num_degrees;
			if (robot.orientation >= 360) {
				robot.orientation -= 360; //Converts a number of degrees >= 360 back between 0 and 360 
									//(Ex. 400 degrees = 40 degrees = 400 degrees - 360 degrees)
			}
			move_log.add_event(Event::Move(index++, robot));
		}

		void forward(double num_inches) { //X and Y are the adjacent and opposite sides of a triangle 
										  //with hypotenuse num_inches and theta orientation
			robot.y += num_inches * sin(robot.orientation * convert_deg);
			robot.x += num_inches * cos(robot.orientation * convert_deg);
			move_log.add_event(Event::Move(index++, robot));
			for (int i = 0; i < blocks.size(); i++) {
				if (intersect(robot, blocks[i])) {
					std::cout << "INTERSECTION!!!!!!!!" << std::endl;
				}
				if (encapsulate(robot, blocks[i])) {
					std::cout << "ENCAPSULATION!!!!!!" << std::endl;
				}
			}
		}

		void backward(double num_inches) { //Same math as forward movement except... backwards...
			robot.y -= num_inches * sin(robot.orientation * convert_deg);
			robot.x -= num_inches * cos(robot.orientation * convert_deg);
			move_log.add_event(Event::Move(index++, robot));
			for (int i = 0; i < blocks.size(); i++) {
				if (intersect(robot, blocks[i])) {
					std::cout << "INTERSECTION!!!!!!!!" << std::endl;
				}
				if (encapsulate(robot, blocks[i])) {
					std::cout << "ENCAPSULATION!!!!!!" << std::endl;
				}
			}
		}

		void right(double num_inches) {
			if (robot.is_mechanum) {
				robot.x += num_inches * sin(robot.orientation * convert_deg);
				robot.y += num_inches * cos(robot.orientation * convert_deg);
				move_log.add_event(Event::Move(index++, robot));
				for (int i = 0; i < blocks.size(); i++) {
					if (intersect(robot, blocks[i])) {
						std::cout << "INTERSECTION!!!!!!!!" << std::endl;
					}
					if (encapsulate(robot, blocks[i])) {
						std::cout << "ENCAPSULATION!!!!!!" << std::endl;
					}
				}
			}
			else {
				rotate_cw(90);
				forward(num_inches);
				rotate_ccw(90);
				move_log.add_event(Event::Move(index++, robot));
			}
		}

		void left(double num_inches) {
			if (robot.is_mechanum) {
				robot.x -= num_inches * sin(robot.orientation * convert_deg);
				robot.y -= num_inches * cos(robot.orientation * convert_deg);
				move_log.add_event(Event::Move(index++, robot));
				for (int i = 0; i < blocks.size(); i++) {
					if (intersect(robot, blocks[i])) {
						std::cout << "INTERSECTION!!!!!!!!" << std::endl;
					}
					if (encapsulate(robot, blocks[i])) {
						std::cout << "ENCAPSULATION!!!!!!" << std::endl;
					}
				}
			}
			else {
				rotate_ccw(90);
				forward(num_inches);
				rotate_cw(90);
				move_log.add_event(Event::Move(index++, robot));
			}
		}

		//Diagonal functions do not take orientation into account
		void diagonal_right_up(double num_inches) {
			if (robot.is_mechanum) {
				robot.x += num_inches;
				robot.y += num_inches;
				move_log.add_event(Event::Move(index++, robot));
			}
			else {
				rotate_cw(robot.orientation -= 45);
				forward(num_inches);
				rotate_ccw(robot.orientation += 45);
				move_log.add_event(Event::Move(index++, robot));
			}
		}

		void diagonal_right_down(double num_inches) {
			if (robot.is_mechanum) {
				robot.x += num_inches;
				robot.y -= num_inches;
				move_log.add_event(Event::Move(index++, robot));
			}
			else {
				rotate_cw(robot.orientation -= (135));
				forward(num_inches);
				rotate_ccw(robot.orientation += (135));
				move_log.add_event(Event::Move(index++, robot));
			}
		}

		void diagonal_left_up(double num_inches) {
			if (robot.is_mechanum) {
				robot.x -= num_inches;
				robot.y += num_inches;
				move_log.add_event(Event::Move(index++, robot));
			}
			else {
				rotate_cw(robot.orientation += 45);
				forward(num_inches);
				rotate_ccw(robot.orientation -= 45);
				move_log.add_event(Event::Move(index++, robot));
			}
		}

		void diagonal_left_down(double num_inches) {
			if (robot.is_mechanum) {
				robot.x -= num_inches;
				robot.y -= num_inches;
				move_log.add_event(Event::Move(index++, robot));
			}
			else {
				rotate_cw(robot.orientation += 135);
				forward(num_inches);
				rotate_ccw(robot.orientation -= 135);
				move_log.add_event(Event::Move(index++, robot));
			}
		}

		bool scan() {
			//Setup scanning variables
			bool something_there = false;
			int scan_radius; //Scan is a portion of a circle surrounding the robot
			if (robot.return_width() > robot.return_length()) {
				scan_radius = robot.return_width() / 2 + robot.return_sensing_distance();
			}
			else {
				scan_radius = robot.return_length() / 2 + robot.return_sensing_distance();
			}

			double lower_angle, upper_angle;

			if (robot.orientation < 180 && robot.orientation >= 0) {
				lower_angle = robot.orientation - (robot.sensing_angle / 2);
				upper_angle = robot.orientation + (robot.sensing_angle / 2);
			}
			else {
				lower_angle = robot.orientation + (robot.sensing_angle / 2);
				upper_angle = robot.orientation - (robot.sensing_angle / 2);
			}
			//Check for mothership
			//Check for blocks
			for (int i = 0; i < blocks.size(); i++) {
				bool is_in_range = false;
				bool is_in_angle = false;

				double delta_x = abs(robot.x - blocks[i].return_x());
				double delta_y = abs(robot.y - blocks[i].return_y());
				double distance_away = sqrt(pow(delta_x, 2) + pow(delta_y, 2)); //Pythagorean theorem
				double angle = atan(delta_y / delta_x);

				if (distance_away <= scan_radius + (blocks[i].return_width() / 2)) {
					is_in_range = true;
				}

				if (angle >= lower_angle || angle <= upper_angle) {
					is_in_angle = true;
				}

				if (is_in_range && is_in_angle) {
					something_there = true;
				}
			}
			//Check for obstacles
			for (int i = 0; i < obstacles.size(); i++) {
				bool is_in_range = false;
				bool is_in_angle = false;

				double delta_x = abs(robot.x - obstacles[i].return_x());
				double delta_y = abs(robot.y - obstacles[i].return_y());
				double distance_away = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
				double angle = atan(delta_y / delta_x);

				if (distance_away <= scan_radius + (obstacles[i].return_radius()/2)) {
					is_in_range = true;
				}

				if (angle >= lower_angle || angle <= upper_angle) {
					is_in_angle = true;
				}

				if (is_in_range && is_in_angle) {
					robot.known_obstacles.push_back(obstacles[i]);
					something_there = true;
				}
			}
			return something_there;
		}

		//void signal_end()


		//Unfinished... Obviously
		//Should only pick up block if it is within a 2" wide by 2" deep square in front of the robot
		//Shape intersection can be determined by the distance between the center points taking the orientation of each
		//object into consideration
		bool pick_up_block(){
			bool successful = false;
			Square pick_up_space(2, 2);
			pick_up_space.set_orientation(robot.orientation);
			pick_up_space.set_x(robot.return_width() + robot.return_x() * cos(robot.orientation));
			pick_up_space.set_y(robot.return_length() + robot.return_y() * sin(robot.orientation));
			for (int i = 0; i < blocks.size(); i++) {
				if (encapsulate(pick_up_space, blocks[i])) {
					successful = true;
					robot.blocks_on_robot.push_back(blocks[i]);
					blocks[i].picked_up();
					break;
				}
			}
			return successful;
		}

		void place_block() {
			return;
		}
	};
}

#endif
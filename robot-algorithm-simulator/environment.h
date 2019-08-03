#pragma once
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <math.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include "global.h"
#include "robot.h"
#include "block.h"
#include "obstacle.h"
#include "event.h"
#include "log.h"
#include "mothership.h"

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
		Rectangle map;
		//Mothership generation
		std::vector<Obstacle> obstacles;
		

		double dist_btwn_pts(Point a, Point b) {
			double diff_x = a.return_x() - b.return_x();
			double diff_y = a.return_y() - b.return_y();
			return sqrt(pow(diff_x, 2) + pow(diff_y, 2));
		}

		//==============================================
		//	Block Generation Functions
		//==============================================
		void generate_blocks(int num_blocks) { //needs to be cleaned up
			srand(static_cast<unsigned> (time(0)));
			if (num_blocks <= 0) { return; }
			for (int i = 0; i < num_blocks; i++) {
				bool next = false;
				int rand_x = 6 + static_cast<double> (rand()) / (static_cast<double> (RAND_MAX / (90 - 6)));
				int rand_y = 6 + static_cast<double> (rand()) / (static_cast<double> (RAND_MAX / (90 - 6)));
				if (i >= 1) {
					Point point(rand_x, rand_y);
					for (int j = 0; j < i; j++) {
						Point block(blocks[j].return_x(), blocks[j].return_y());
						if (dist_btwn_pts(point, block) <= 6) {
							i--;//redo this block
							next = true;
							break;
						}
					}
					if (next) { continue; }
					if (obstacles.size() > 0) {
						for (int j = 0; j < i; j++) {
							Point obstacle(obstacles[j].return_x(), obstacles[j].return_y());
							if (dist_btwn_pts(point, obstacle) <= 6) {
								i--;//redo this block
								next = true;
								break;
							}
						}
					}
					if (next) { continue; }
					Point robot_center(robot.return_x(), robot.return_y()); 
					//Fix so that it checks intersection with a square not a circle
					if (dist_btwn_pts(robot_center, point) <= 6 + (blocks[0].return_width() / 2)) {
						i--;//redo this block
						continue;
					}
				}
				
				//Set max and min to be edges of map taking the size of the obstacle into account
				blocks.push_back(Block(rand_x, rand_y, rand_x, rand_y, 'A', 0));
				block_creation_log.add_event(Event::Block_Creation(index++, blocks[i]));
			}
		}
		//==============================================
		//	Block Movement Functions
		//==============================================

		//==============================================
		//	Obstacle Generation Functions
		//==============================================
		void generate_obstacles(int num_obstacles) {
			if (num_obstacles <= 0) { return; }
			for (int i = 0; i < num_obstacles; i++) {
				bool next = false;
				int rand_x = 6 + static_cast<double> (rand()) / (static_cast<double> (RAND_MAX / (90 - 6)));
				int rand_y = 6 + static_cast<double> (rand()) / (static_cast<double> (RAND_MAX / (90 - 6)));
				if (i >= 1) {
					Point point(rand_x, rand_y);
					for (int j = 0; j < i; j++) {
						Point obstacle(obstacles[j].return_x(), obstacles[j].return_y());
						if (dist_btwn_pts(point, obstacle) <= 6) {
							i--;//redo this block
							next = true;
							break;
						}
					}
					if (next) { continue; }
					if (blocks.size() > 0) {
						for (int j = 0; j < blocks.size(); j++) {
							Point block(blocks[j].return_x(), blocks[j].return_y());
							if (dist_btwn_pts(point, block) <= 6) {
								i--;//redo this block
								next = true;
								break;
							}
						}
					}
					if (next) { continue; }
					Point robot_center(robot.return_x(), robot.return_y());
					//Fix so that it checks intersection with a square not a circle
					if (dist_btwn_pts(robot_center, point) <= 6 + (blocks[0].return_width() / 2)) {
						i--;//redo this block
						continue;
					}
				}

				//Set max and min to be edges of map taking the size of the obstacle into account
				//make these obstacle logs
				obstacles.push_back(Obstacle(rand_x, rand_y));
				obst_creation_log.add_event(Event::Obstacle_Creation(index++, obstacles[i]));
			}
		}
		//==============================================
		//	Obstacle Movement Functions
		//==============================================

		//==============================================
		//	Shape Intersection Function
		//==============================================
		
		
		bool collision_circle(Obstacle obstacle) { //Untested
			
			//Check if the circle intersects any of the corners of the robot
			std::vector<Point> points;
			points.push_back(robot.top_right);
			points.push_back(robot.top_left);
			points.push_back(robot.bottom_right);
			points.push_back(robot.bottom_left);

			Point obst_center(obstacle.return_x(), obstacle.return_y());

			for (int i = 0; i < points.size(); i++) {
				points[i].set_distance(obst_center);
				if (points[i].distance <= obstacle.return_radius()) { return true; }
			}

			//Sort the points by distance away from the obstacle
			std::sort(points.begin(), points.end(), less_than());

			double m = (points[0].x - points[1].x) / (points[0].y - points[1].y);
			double b = points[0].y - (m * points[0].x);

			double m_perp = 1 / m;
			double b_perp = obst_center.y - (m * obst_center.x);

			double new_x = (b - b_perp) / (m_perp - m);
			double new_y = m_perp * new_x + b_perp;

			double diff_x = obst_center.x - new_x;
			double diff_y = obst_center.y - new_y;
			double distance = sqrt(pow(diff_x, 2) + pow(diff_y, 2));

			if (distance <= obstacle.return_radius()) { return true; }
			else { return false; }
		}
		
		bool intersect_rect(Robot robot, Rectangle& rect) {
			bool intersects = false;

			return intersects;
		}

	public:
		Log <Event::Move> move_log;
		Log <Event::Block_Creation> block_creation_log;
		Log <Event::Robot_Creation> robot_creation_log;
		Log <Event::Obstacle_Creation> obst_creation_log;

		Environment(Robot &main_robot, Rectangle &i_map, 
			int num_blocks = 0, int num_obstacles = 0, 
			bool rand_blocks = true, bool rand_obstacles = true): 
			robot(main_robot) {
			move_log.add_event(Event::Move(index, robot), true); //Set initial poisition
			robot_creation_log.add_event(Event::Robot_Creation(index++, robot));
			generate_blocks(num_blocks);
			generate_obstacles(num_obstacles);
		}

		Block return_block(int ind) {
			return blocks[ind];
		}

		Obstacle return_obst(int ind) {
			return obstacles[ind];
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
			double increment = 0;
			bool collision = false;
			while (increment <= num_inches) {
				for (int i = 0; i < obstacles.size(); i++) {
					if (collision_circle(obstacles[i])) {
						obstacles[i].has_been_hit = true;
						collision = true;
						std::cout << "COLLISION" << std::endl;
					}
				}
				if (collision) { break; }
				robot.y += increment * sin(robot.orientation * convert_deg);
				robot.x += increment * cos(robot.orientation * convert_deg);
				move_log.add_event(Event::Move(index++, robot));
				increment += 0.01;
			}
			
		}

		void backward(double num_inches) { //Same math as forward movement except... backwards...
			double increment = 0;
			bool collision = false;
			while (increment <= num_inches) {
				for (int i = 0; i < obstacles.size(); i++) {
					if (collision_circle(obstacles[i])) {
						obstacles[i].has_been_hit = true;
						collision = true;
						std::cout << "COLLISION" << std::endl;
					}
				}
				if (collision) { break; }
				robot.y -= increment * sin(robot.orientation * convert_deg);
				robot.x -= increment * cos(robot.orientation * convert_deg);
				move_log.add_event(Event::Move(index++, robot));
				increment += 0.01;
			}
			
		}

		void right(double num_inches) {
			if (robot.is_mechanum) {
				robot.x += num_inches * sin(robot.orientation * convert_deg);
				robot.y -= num_inches * cos(robot.orientation * convert_deg);
				move_log.add_event(Event::Move(index++, robot));
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
				robot.y += num_inches * cos(robot.orientation * convert_deg);
				move_log.add_event(Event::Move(index++, robot));
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

				double delta_x = abs(robot.x - blocks[i].x);
				double delta_y = abs(robot.y - blocks[i].y);
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
		/*
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
		*/
		void place_block() {
			return;
		}
	};
}

#endif
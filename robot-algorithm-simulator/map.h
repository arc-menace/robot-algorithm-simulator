#pragma once
#ifndef MAP_H
#define MAP_H

#include "rmas6219.h"
#include "block.h"
#include "obstacle.h"

namespace rmas {
	class Map {
	public:
		void set_map_size(double size) {
			if (size > 96.0) {
				map_size = DEFAULT_BOARD_SIZE;
			}
			else if (size < 0.0) {
				map_size = 0.0;
			}
			else {
				map_size = size;
			}
		}

		void load_block(Block block) {
			blocks_on_map.push_back(block);
		}

		void load_obstacle(Obstacle obstacle) {
			obstacles_on_map.push_back(obstacle);
		}

	private:
		double map_size = DEFAULT_BOARD_SIZE;
		vector<Block> blocks_on_map; //The blocks which have not been picked up by the robot
		vector<Obstacle> obstacles_on_map; //obstacles on the map
	};
}

#endif
#include "rmas6219.h"

//Obstacle Class
class Obstacle {
public:
	int stated_x, stated_y; //Location on map.
	Obstacle(int x_coordinate, int y_coordinate) {
		stated_x = x_coordinate;
		stated_y = y_coordinate;
	}
};
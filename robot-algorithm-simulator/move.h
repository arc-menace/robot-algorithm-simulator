#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

namespace rmas {
	class Move {
	public:
		double x, y, orientation;
		Move(double init_x, double init_y, double init_orientation) {
			x = init_x;
			y = init_y;
			orientation = init_orientation;
		}
	};
}

#endif
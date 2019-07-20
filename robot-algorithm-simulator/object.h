#pragma once
#ifndef OBJECT_H
#define OBJECT_H

namespace rmas {
	class Object {
		double x, y;
	public:
		Object(double i_x, double i_y) {
			x = i_x;
			y = i_y;
		}
		double return_x() {
			return x;
		}
		double return_y() {
			return y;
		}
	};
}

#endif
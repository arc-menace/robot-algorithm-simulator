#pragma once
#ifndef OBJECT_H
#define OBJECT_H

namespace rmas {
	enum class Shape {
		SQUARE,
		CIRCLE,
		COMPOUND,
	};

	class Object {
		double x, y;
		Shape shape = Shape::SQUARE;
		double orientation = 0;
	public:
		Object() {
			x = 0; 
			y = 0;
		}
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
		Shape return_shape() {
			return shape;
		}
		double return_orientation() {
			return orientation;
		}
		void set_x(double i_x) {
			x = i_x;
		}
		void set_y(double i_y) {
			y = i_y;
		}
		void set_orientation(double i_orient) {
			orientation = i_orient;
		}
	};

	class Square : public Object {
		double width = 0;
		double length = 0;
		Shape shape = Shape::SQUARE;
	public:
		Square(double i_width, double i_length) {
			width = i_width;
			length = i_length;
		}
		double return_width() {
			return width;
		}
		double return_length() {
			return length;
		}
		double return_radius() {
			return 0;
		}
	};
}

#endif
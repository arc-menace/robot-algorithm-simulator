#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <math.h>
#include "global.h"

namespace rmas {

	enum class Shape {
		RECTANGLE,
		CIRCLE,
		COMPOUND,
		POINT
	};

	class Point {
	public:
		double x = 0;
		double y = 0;
		double distance = 0;
		Point(double t_x = 0, double t_y = 0) : x(t_x), y(t_y) {}

		double return_x() { return x; }
		double return_y() { return y; }

		void set_distance(Point b) {
			double diff_x = x - b.return_x();
			double diff_y = y - b.return_y();
			distance = sqrt(pow(diff_x, 2) + pow(diff_y, 2));
		}
	};

	struct less_than {
		bool operator() (const Point& a, const Point& b) { return (a.distance > b.distance); }
	};
	

	class Object {
	public:
		friend class Environment;
		
		double x = 0;
		double y = 0;
		double orientation = 0;
		Shape shape = Shape::POINT;
		std::string name = "Object";

		Object(double t_x, double t_y, double i_orient = 0,
			Shape shape = Shape::POINT,
			std::string i_name = "Object"): x(t_x), y(t_y),
			orientation(i_orient), name(i_name) {}

		double return_x() { return x; }
		double return_y() { return y; }
		double return_orientation() { return orientation; }
		Shape return_shape() { return shape; }
		std::string return_name() { return name; }
	};

	class Rectangle : public Object {
	public:
		double width = 0;
		double length = 0;
		const Shape shape = Shape::RECTANGLE;
		Point top_right;
		Point top_left;
		Point bottom_right;
		Point bottom_left;

		Rectangle(double i_x = 0, double i_y = 0, double i_width = 0,
			double i_length = 0, double orient = 0,
			std::string i_name = "Rectangle"): 
			Object(i_x, i_y, orient, shape, i_name), 
			width(i_width), 
			length(i_length), 

			//If the rectangle's orientation is 0, then the top right point the vertex of a right triangle with a 45 degree angle.
			//Similarly for the other points increasing increments of 90 degrees. All values are converted to radians to use the
			//sin and cos functions from math.h
			top_right(x + (width / 2) * cos(orientation + convert_deg * PI / 4), y + (length / 2) * sin(orientation + convert_deg * PI / 4)), 
			top_left(x + (width / 2) * cos(orientation + convert_deg * 3 * PI / 4), y + (length / 2) * sin(orientation + convert_deg * 3 * PI / 4)),
			bottom_right(x + (width / 2) * cos(orientation + convert_deg * 5 * PI / 4), y + (length / 2) * sin(orientation + convert_deg * 5 * PI / 4)),
			bottom_left(x + (width / 2) * cos(orientation + convert_deg * 7 * PI / 4), y + (length / 2) * sin(orientation + convert_deg * 7 * PI / 4)) {}
		
		double return_width() { return width; }
		double return_length() { return length; }
	};

	class Circle : public Object {
	public:
		double radius;
		const Shape shape = Shape::CIRCLE;

		Circle(double i_x, double i_y, double i_radius, std::string i_name = "Circle"):
			Object(i_x, i_y, 0.0, shape, i_name), radius(i_radius) {}

		double return_radius() { return radius;}
	};

	class Compound : public Object {
	public:
		//This is a really sloppy way to do this, but will work for the time being
		std::vector<Rectangle> rects;
		const Shape shape = Shape::COMPOUND;

		Compound(double i_x, double i_y, double i_orientation, 
			std::vector<Rectangle> i_rects): 
			Object(i_x, i_y, i_orientation, Shape::COMPOUND, "Compound"),
			rects(i_rects) {}
	};
}

#endif
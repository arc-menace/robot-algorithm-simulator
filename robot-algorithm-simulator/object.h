#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <string>

namespace rmas {

	enum class Shape {
		RECTANGLE,
		CIRCLE,
		COMPOUND,
		POINT
	};

	class Object {
	public:
		friend class Environment;

		double x = 0;
		double y = 0;
		double orientation = 0;
		Shape shape = Shape::POINT;
		std::string name = "Object";

		Object(double i_x, double i_y, double i_orient = 0,
			Shape shape = Shape::POINT,
			std::string i_name = "Object") :
			x(i_x), y(i_y), orientation(i_orient), name(i_name) {}

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

		Rectangle(double i_x = 0, double i_y = 0, double i_width = 0,
			double i_length = 0, double orientation = 0,
			std::string i_name = "Rectangle"): 
			Object(i_x, i_y, orientation, shape, i_name), 
			width(i_width), length(i_length) {}

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
		std::vector<Circle> circs;
		const Shape shape = Shape::COMPOUND;

		Compound(double i_x, double i_y, double i_orientation, 
			std::vector<Rectangle> i_rects, std::vector<Circle> i_circs): 
			Object(i_x, i_y, i_orientation, Shape::COMPOUND, "Compound"),
			rects(i_rects), circs(i_circs) {}
	};
}

#endif
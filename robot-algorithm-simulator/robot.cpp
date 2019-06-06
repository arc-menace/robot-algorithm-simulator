#include "robot.h"

Robot::Robot(double current_x = DEFAULT_START, double current_y = DEFAULT_START) {
	x = current_x;
	y = current_y;
	starting_x = x;
	starting_y = y;
}

void Robot::rotate_cw(double num_degrees) { //Rotate Clockwise
	orientation -= num_degrees;
	if (orientation < 0) {
		orientation += 360; //Converts a negative number of degrees to positive 
							//(Ex. -40 degrees = 320 degrees = -40 degrees + 360 degrees)
	}
}
void Robot::rotate_ccw(double num_degrees) { //Rotate CounterClockwise
	orientation += num_degrees;
	if (orientation >= 360) {
		orientation -= 360; //Converts a number of degrees >= 360 back between 0 and 360 
							//(Ex. 400 degrees = 40 degrees = 400 degrees - 360 degrees)
	}
}
void Robot::forward(double num_inches) { //X and Y are the adjacent and opposite sides of a triangle 
							   //with hypotenuse num_inches and theta orientation
	y += num_inches * sin(orientation);
	x += num_inches * cos(orientation);
}
void Robot::backward(double num_inches) { //Same math as forward movement except... backwards...
	y -= num_inches * sin(orientation);
	x -= num_inches * cos(orientation);
}
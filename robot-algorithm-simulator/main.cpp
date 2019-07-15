#include "rmas6219.h"

int main() {
	rmas::Robot robot;
	robot.print_atts();
	robot.forward(12);
	robot.print_atts();
	robot.left(12);
	robot.print_atts();
	return 0;
}
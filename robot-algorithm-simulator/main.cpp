#include "rmas6219.h"

using namespace rmas;

int main() {
	/*
		Graphics Function:
		takes the logs. Each event has a number assigned by the order it occured in the simulation
		Graphics copies each log to a throw away vector
		as it used the events to animate, it remebers where it was, so that it isn't scanning through whole vectors.
	*/

	//define robot
	Robot robot;
	//define blocks/obstacles if applicable

	//build environment
	Environment environment(robot);

	//run algorithm
	environment.forward(12);
	environment.rotate_ccw(90);

	//show results

	return 0;
}
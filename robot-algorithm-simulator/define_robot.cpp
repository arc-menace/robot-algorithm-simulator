#include "rmas6219.h"

using namespace rmas;
using std::cout;
using std::cin;
using std::endl;

void define_robot(Robot& robot, Rectangle map, bool advanced = false) {
	double x = DEFAULT_ROBOT_X;
	double y = DEFAULT_ROBOT_Y;
	double orientation = DEFAULT_START_ORIENTATION;
	double width = MAX_ROBOT_WIDTH;
	double length = MAX_ROBOT_LENGTH;
	double sensing_distance = MAX_SENSE_DIST;
	double sensing_angle = DEFAULT_SENSE_ANGLE;
	double wheel_diameter = DEFAULT_WHEEL_DIAM;
	bool mechanum = DEFAULT_MECHANUM;

	bool loop = true;
	while (loop) {
		cout << "Select and Option:\n\n"
			<< "1)\tStarting position: (" << x << "," << y << ")" << endl
			<< "2)\tStarting Orientation: " << orientation << endl
			<< "3)\tSensing Distance and Angle: " << sensing_distance << " " << sensing_angle << char(248) << endl;

		if (!advanced) {
			cout << "4)\tReset to defaults" << endl
				<< "5)\tChange All" << endl
				<< "6)\tContinue to next Item" << endl;
		}

		else {
			cout << "4)\tWidth: " << width << endl
				<< "5)\tLength: " << length << endl;
			cout << "6)\tMechanum Drive: ";
			if (mechanum) {
				cout << "Enabled" << endl;
			}
			else {
				cout << "Disabled" << endl;
			}
			cout << "7)\tWheel Diameter: " << wheel_diameter << endl
				<< "8)\tChange All" << endl
				<< "9)\tReset to Defaults" << endl
				<< "10)\tContinue to next Item" << endl;
		}
		cout << endl;

		int choice;
		get_input(choice);

		switch (choice) {
		case 1:
			cout << "Enter the starting X: ";
			get_input(x);
			while (x < (width / 2) || x > (map.return_width() - (width / 2))) { //check position on map. Cannot Fall off on spawn
				std::cerr << "ERROR: Robot must be spawed fully on map" << endl;
				get_input(x);
			}

			cout << "Enter the starting Y: ";
			get_input(y);
			while (y < (length / 2) || y >(map.return_length() - (length / 2))) { //check position on map. Cannot Fall off on spawn
				std::cerr << "ERROR: Robot must be spawed fully on map" << endl;
				get_input(y);
			}
			cout << endl;
			break;

		case 2:
			cout << "Enter the starting orientation in degrees: ";
			get_input(orientation);
			if (orientation >= 360) {
				while (orientation >= 360) { orientation -= 360; }
				cout << "Orientation greater than 360. Adjusted down to " << orientation << endl;
			}

			if (orientation < 0) {
				while (orientation < 0) { orientation += 360; }
				cout << "Orientation cannot be negative. Adjusted to " << orientation << endl;
			}
			cout << endl;
			break;

		case 3:
			cout << "Enter the sensing distance: ";
			get_input(sensing_distance);
			while (sensing_distance > MAX_SENSE_DIST || sensing_distance < MIN_SENSE_DIST) {
				std::cerr << ERROR_WRONG_VAL << endl;
				get_input(sensing_distance);
			}

			cout << "Enter the sensing angle in degrees: ";
			get_input(sensing_angle);
			if (sensing_angle >= 360) {
				while (sensing_angle > 360) { sensing_angle -= 360; }
				cout << "Angle greater than 360. Adjusted down to " << sensing_angle << endl;
			}

			if (sensing_angle < 0) {
				while (sensing_angle < 0) { sensing_angle += 360; }
				cout << "Angle cannot be negative. Adjusted to " << sensing_angle << endl;
			}
			break;

		case 4:
			if (advanced) {
				cout << "Enter the Robot's width: ";
				get_input(width);
				while (width > MAX_ROBOT_WIDTH || width <= 0) {
					std::cerr << ERROR_WRONG_VAL << endl;
				}
			}
			else {
				x = DEFAULT_ROBOT_X;
				y = DEFAULT_ROBOT_Y;
				orientation = DEFAULT_START_ORIENTATION;
				sensing_distance = MAX_SENSE_DIST;
				sensing_angle = DEFAULT_SENSE_ANGLE;
			}
			break;

		case 5:
			if (advanced) {
				cout << "Enter the Robot's length: ";
				get_input(length);
				while (length > MAX_ROBOT_LENGTH || length <= 0) {
					std::cerr << ERROR_WRONG_VAL << endl;
				}
			}
			else {
				cout << "Enter the starting X: ";
				get_input(x);
				while (x < (width / 2) || x >(map.return_width() - (width / 2))) { //check position on map. Cannot Fall off on spawn
					std::cerr << "ERROR: Robot must be spawed fully on map" << endl;
					get_input(x);
				}

				cout << "Enter the starting Y: ";
				get_input(y);
				while (y < (length / 2) || y >(map.return_length() - (length / 2))) { //check position on map. Cannot Fall off on spawn
					std::cerr << "ERROR: Robot must be spawed fully on map" << endl;
					get_input(y);
				}

				cout << "Enter the starting orientation in degrees: ";
				get_input(orientation);
				if (orientation >= 360) {
					while (orientation >= 360) { orientation -= 360; }
					cout << "Orientation greater than 360. Adjusted down to " << orientation << endl;
				}
				if (orientation < 0) {
					while (orientation < 0) { orientation += 360; }
					cout << "Orientation cannot be negative. Adjusted to " << orientation << endl;
				}

				cout << "Enter the sensing distance: ";
				get_input(sensing_distance);
				while (sensing_distance > MAX_SENSE_DIST || sensing_distance < MIN_SENSE_DIST) {
					std::cerr << ERROR_WRONG_VAL << endl;
					get_input(sensing_distance);
				}

				cout << "Enter the sensing angle in degrees: ";
				get_input(sensing_angle);
				if (sensing_angle >= 360) {
					while (sensing_angle > 360) { sensing_angle -= 360; }
					cout << "Angle greater than 360. Adjusted down to " << sensing_angle << endl;
				}

				if (sensing_angle < 0) {
					while (sensing_angle < 0) { sensing_angle += 360; }
					cout << "Angle cannot be negative. Adjusted to " << sensing_angle << endl;
				}
			}
			break;
		
		case 6:
			if (advanced) {
				cout << "Enable Mechanum Drive? Y/N";
				char answer;
				get_input(answer);
				while (answer != 'Y' &&
					answer != 'y' &&
					answer != 'N' &&
					answer != 'n') {
					get_input(answer);
				}
				if (answer == 'Y' || answer == 'y') { mechanum = true; }
				else { mechanum = false; }
			}

			else {
				loop = false;
			}
			break;
			
		case 7:
			if (advanced) {
				cout << "Enter the diameter of the Wheels (This enables distance tracking): ";
				get_input(wheel_diameter);
				while (wheel_diameter < 0 || wheel_diameter > MAX_WHEEL_DIAM) {
					std::cerr << ERROR_WRONG_VAL << endl;
				}
			}
			else {
				std::cerr << ERROR_INVALID_INPUT << endl;
			}
			break;

		case 8:
			if (advanced) {
				cout << "Enter the starting X: ";
				get_input(x);
				while (x < (width / 2) || x >(map.return_width() - (width / 2))) { //check position on map. Cannot Fall off on spawn
					std::cerr << "ERROR: Robot must be spawed fully on map" << endl;
					get_input(x);
				}

				cout << "Enter the starting Y: ";
				get_input(y);
				while (y < (length / 2) || y >(map.return_length() - (length / 2))) { //check position on map. Cannot Fall off on spawn
					std::cerr << "ERROR: Robot must be spawed fully on map" << endl;
					get_input(y);
				}

				cout << "Enter the starting orientation in degrees: ";
				get_input(orientation);
				if (orientation >= 360) {
					while (orientation >= 360) { orientation -= 360; }
					cout << "Orientation greater than 360. Adjusted down to " << orientation;
				}
				if (orientation < 0) {
					while (orientation < 0) { orientation += 360; }
					cout << "Orientation cannot be negative. Adjusted to " << orientation;
				}

				cout << "Enter the sensing distance: ";
				get_input(sensing_distance);
				while (sensing_distance > MAX_SENSE_DIST || sensing_distance < MIN_SENSE_DIST) {
					std::cerr << ERROR_WRONG_VAL << endl;
					get_input(sensing_distance);
				}

				cout << "Enter the sensing angle in degrees: ";
				get_input(sensing_angle);
				if (sensing_angle >= 360) {
					while (sensing_angle > 360) { sensing_angle -= 360; }
					cout << "Angle greater than 360. Adjusted down to " << sensing_angle << endl;
				}

				if (sensing_angle < 0) {
					while (sensing_angle < 0) { sensing_angle += 360; }
					cout << "Angle cannot be negative. Adjusted to " << sensing_angle << endl;
				}

				cout << "Enter the Robot's width: ";
				get_input(width);
				while (width > MAX_ROBOT_WIDTH || width <= 0) {
					std::cerr << ERROR_WRONG_VAL << endl;
				}

				cout << "Enter the Robot's length: ";
				get_input(length);
				while (length > MAX_ROBOT_LENGTH || length <= 0) {
					std::cerr << ERROR_WRONG_VAL << endl;
				}

				cout << "Enable Mechanum Drive? Y/N";
				char answer;
				get_input(answer);
				while (answer != 'Y' &&
					answer != 'y' &&
					answer != 'N' &&
					answer != 'n') {
					get_input(answer);
				}
				if (answer == 'Y' || answer == 'y') { mechanum = true; }
				else { mechanum = false; }

				cout << "Enter the diameter of the Wheels (This enables distance tracking): ";
				get_input(wheel_diameter);
				while (wheel_diameter < 0 || wheel_diameter > MAX_WHEEL_DIAM) {
					std::cerr << ERROR_WRONG_VAL << endl;
				}
			}
			else {
				std::cerr << ERROR_INVALID_INPUT << endl;
			}
			break;
			
		case 9:
			if (advanced) {
				x = DEFAULT_ROBOT_X;
				y = DEFAULT_ROBOT_Y;
				orientation = DEFAULT_START_ORIENTATION;
				width = MAX_ROBOT_WIDTH;
				length = MAX_ROBOT_LENGTH;
				sensing_distance = MAX_SENSE_DIST;
				sensing_angle = DEFAULT_SENSE_ANGLE;
				wheel_diameter = DEFAULT_WHEEL_DIAM;
				mechanum = DEFAULT_MECHANUM;
			}
			else {
				std::cerr << ERROR_INVALID_INPUT << endl;
			}
			break;

		case 10:
			if (advanced) {
				loop = false;
				break;
			}
			else {
				std::cerr << ERROR_INVALID_INPUT << endl;
				break;
			}
			
		default:
			std::cerr << ERROR_INVALID_INPUT << endl;
		}
		if (!loop) { break; }
	}
	robot.~Robot();
	new(&robot) Robot(mechanum, x, y, width, length, orientation, sensing_distance, sensing_angle, wheel_diameter);
	cout << endl;
}

void define_blocks(std::vector<Block>& blocks, bool advanced = false) {
	
	return;
}
void define_obstacles(std::vector<Obstacle>& obstacles, bool advanced = false) {
	
	return;
}

void define_mothership(Mothership& mothership, bool advanced = false) {
	
	return;
}

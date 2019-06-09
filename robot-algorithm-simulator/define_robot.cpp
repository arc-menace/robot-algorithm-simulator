#include "rmas6219.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::numeric_limits;
using std::streamsize;


Robot define_robot() {

	//Get starting position of the robot
	cout << "Please enter the starting position of the robot (Ex. x y): ";
	int starting_x, starting_y;
	cin.clear();
	cin >> starting_x >> starting_y;
	//Input error handling:
	while (cin.fail() || starting_x > board_size || starting_y > board_size)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error with input. Please try again: ";
		cin >> starting_x >> starting_y;
	}
	cout << endl;

	Robot Crunchy(starting_x, starting_y);

	//Robot Dimensions
	cout << "Please enter the width and length of the robot in inches (Ex. 12 12): ";
	float robot_length, robot_width;
	cin >> robot_length >> robot_width;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error with input. Please try again: ";
		cin >> robot_length >> robot_width;
	}
	cout << endl;

	Crunchy.width = robot_width;
	Crunchy.length = robot_length;

	cout << "How close to an obstacle does the robot need to be in order to detect it?\nAnswer: ";
	double sensing;
	cin >> sensing;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error with input. Please try again: ";
		cin >> sensing;
	}
	cout << endl;
	
	Crunchy.set_sensing_distance(sensing);

	return Crunchy;
}
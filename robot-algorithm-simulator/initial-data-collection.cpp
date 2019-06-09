/*
#include "rmas6219.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::string;
using std::vector;
using std::numeric_limits;
using std::streamsize;

//Constants:
#define MIN_MAP_DISTANCE 0
#define DEFAULT_START 48
#define NOT_USING_EXISTING_DATA 'N'

//Need to find a way to get the map variable and block/obstalce objects out of this function.

Robot define_robot() {
	

	//=================================================================

	//Initiallize Robot Data
	//=================================================================

	

	cout << "Checking for existing obstacle data." << endl;
	ifstream infile("obstacles.txt"); //Create Input stream handler
	vector <Obstacle> obstacles;
	bool existing_obstacle_data;

	if (!infile) { //If there is an error opening the file or the file does not exist
		cout << "Error with opening file. Previous data does not exist or has been moved.";
		infile.close();
		existing_obstacle_data = false;
	}
	else {
		existing_obstacle_data = true;
		int x, y;
		while (infile) {

			infile >> x >> y;
			obstacles.push_back(Obstacle(x, y));
			x = 0;
			y = 0;
		}
		cout << "There are " << obstacles.size() - 1 << " Existing obstacles are located at ";
		for (unsigned int i = 0; i < obstacles.size() - 1; i++) {
			//There is a bug in the input which adds the last obstacle to the vector twice.
			//This is solved by simply not printing the last piece of the vector
			cout << "(" << obstacles[i].stated_x << "," << obstacles[i].stated_y << ") ";
		}
		cout << endl << "Would you like to change these obstacles? (Y/N)" << endl;
		cout << "Choice: ";
		cin >> answer;
		while (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n') {
			cout << "Error with input. Please try again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> answer;
		}
		cout << endl;
		infile.close(); //Close so that ofstream can be used
	}
	//If there is no existing obstacle data or the user wants to chenge the locations of the obstalces
	if (!existing_obstacle_data || answer == 'Y' || answer == 'y') {
		obstacles.clear(); //destroy all elements in the obstacle vector
		cout << "Please enter the number of obstacles: ";
		int num_obstacles;
		cin >> num_obstacles;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error with input. Please try again: ";
			cin >> num_obstacles;
		}
		cout << endl;

		cout << "Please enter the coordinates for each obstacle (Ex. x1 y1 x2 y2): ";
		for (int i = 0; i < num_obstacles; i++) {
			int x, y;
			cin >> x >> y;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Error with input. Please try again: ";
				cin >> x >> y;
			}
			cout << endl;

			obstacles.push_back(Obstacle(x, y));
		}

		//Output obstacle locations to .txt file to be retrieved the next time the program is run
		ofstream outfile("obstacles.txt");
		for (unsigned int i = 0; i < obstacles.size(); i++) {
			outfile << obstacles[i].stated_x << " " << obstacles[i].stated_y << endl;
		}
		outfile.close();
	}
	obstacles.pop_back();
}
*/
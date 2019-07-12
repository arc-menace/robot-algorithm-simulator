#include "rmas6219.h"
#include <iostream>

void menu() {
	cout << "1.\tRun Simulation\n"
		<< "2.\tChange Simulation Settings\n"
		<< "3.\tAdvanced Settings\n"
		<< "4.\tRestore Default Values\n"
		<< "Selection: ";
	int selection;
	cin >> selection;
	while (selection != 1 && selection != 2 && selection != 3 && selection != 4) {
		cerr << ERROR_INVALID_INPUT << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Selection: ";
		cin >> selection;
	}
	switch (selection) {
	case 1: //returns to the main function to run the algorithm
		return;
	case 2: //Runs definition functions
		
	case 3: //Reruns all functions but enables advanced options parameter
		
	case 4: //Resets core variables to global constants in global.h
		return;
	}
}


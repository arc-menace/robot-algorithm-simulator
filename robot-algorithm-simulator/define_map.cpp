#include <iostream>
#include "rmas6219.h"

using namespace rmas;
using std::cout;
using std::cin;
using std::endl;

void define_map(Rectangle& map) {
	double width = DEFAULT_BOARD_SIZE;
	double length = DEFAULT_BOARD_SIZE;

	bool loop = true;
	while (loop) {
		cout << "Select and Option:\n\n"
			<< "1)\tMap width: " << width << endl
			<< "2)\tMap length: " << length << endl
			<< "3)\tChange All" << endl
			<< "4)\tReset to Defaults" << endl
			<< "5)\tContinue to next item" << endl;
		int choice;
		get_input(choice);
		switch (choice) {
		case 1:
			cout << "Enter Map Width: ";
			get_input(width);
			while (width <= 0) {
				std::cerr << ERROR_WRONG_VAL << endl;
				get_input(width);
			}
			break;

		case 2:
			cout << "Enter Map Length: ";
			get_input(length);
			while (length <= 0) {
				std::cerr << ERROR_WRONG_VAL << endl;
				get_input(length);
			}
			break;

		case 3:
			cout << "Enter Map Width: ";
			get_input(width);
			while (width <= 0) {
				std::cerr << ERROR_WRONG_VAL << endl;
				get_input(width);
			}

			cout << "Enter Map Length: ";
			get_input(length);
			while (length <= 0) {
				std::cerr << ERROR_WRONG_VAL << endl;
				get_input(length);
			}
			break;

		case 4:
			width = DEFAULT_BOARD_SIZE;
			length = DEFAULT_BOARD_SIZE;
			break;

		case 5:
			loop = false;
			break;

		default:
			std::cerr << ERROR_WRONG_VAL << endl;
		}
		if (!loop) { break; }
	}
	return;
}
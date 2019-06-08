#include "rmas6219.h"
#include <iostream>
#include <fstream>


using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::numeric_limits;
using std::streamsize;

void define_map() {
	//Initialize Map Data: 
	//=================================================================

	

	char answer;

	cout << "Checking for existing state file." << endl;
	ifstream inf("mapData.txt"); //Create Input stream handler

	if (!inf) { //If there is an error opening the file or the file does not exist
		cout << "Error with opening file. Previous data does not exist or has been moved." << endl;
		inf.close();
	}
	else {
		inf >> board_size; //Retrieve existing map size and confirm with user whether to use it or replace it
		cout << "The map is set at " << board_size << " inches x " << board_size << " inches. Would you like to change this value? (Y/N)" << endl;
		cout << "Choice: ";
		answer = read_input<char>(true);
		cout << endl;
		inf.close(); //Allows ofstream to be used
	}

	if (board_size == MIN_MAP_LENGTH || answer == 'Y' || answer == 'y') {
		cout << "Please enter the length of one of the sides of the square map in inches: ";
		board_size = read_input<int>();

		//Output new map size to .txt file to be retrieved the next time the program is run
		ofstream outf("mapData.txt");
		outf << board_size << endl;
		outf.close();
	}
}
#pragma once
#ifndef READ_INPUT_H
#define READ_INPUT_H

#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::vector;

template <typename var> var read_input(bool prohibited_answer, vector <var> prohibited_exclusive = {}) {
	var input;
failed_input:
	cin >> input;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error with input. Please Try Again: ";
		cin >> input;
	}
	if (prohibited_answer == true) { //All answers are acceptable except for THESE
		for (int i : prohibited_exclusive) {
			if (input == prohibited_exclusive[i]) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Error with input. Please Try Again: ";
				goto failed_input; //Restart Function.
			}
		}
	}
	else { //Answers are exclusive (only THESE answers are accepted).
		for (int i : prohibited_exclusive) {
			if (input == prohibited_exclusive[i]) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Error with input. Please Try Again: ";
				goto failed_input; //Restart Function.
			}
		}
	}

	cout << endl;

	return input;
}

#endif READ_INPUT_H
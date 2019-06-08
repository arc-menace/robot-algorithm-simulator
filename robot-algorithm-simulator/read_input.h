#pragma once
#ifndef READ_INPUT_H
#define READ_INPUT_H

#include "rmas6219.h"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::vector;

template <typename var> var read_input(bool yes_no = false) {
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

	vector<char> exclusive_answers{ 'Y', 'y', 'N', 'n' };

	if (yes_no) {
		for (int i : exclusive_answers) {
			if (input == exclusive_answers[i]) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Error with input. Please Try Again: ";
				goto failed_input;
			}
		}
	}

	cout << endl;
	return input;
}

#endif
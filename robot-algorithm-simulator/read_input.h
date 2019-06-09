#pragma once
#ifndef READ_INPUT_H //Header Guards to prevent multiple definition problems
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

template <typename var> var read_input(bool is_yes_no_question = false) {
	var input; 
failed_input: //If there is a problem with the input, restart the function
	cin >> input;

	while (cin.fail()) //If there is a system problem with the input (i.e. string entered for int variable)
	{
		cin.clear(); //Clear Input
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignore anything else in the stream (spaces separate values 
															 //in the stream unless using getline())
		cout << "Error with input. Please Try Again: "; //Ends cin.ignore()
		cin >> input; //Take input again
	}

	char exclusive_answers{ 'Y', 'y', 'N', 'n' }; //If the question is yes or no then the only input you want are these chars

	bool input_is_forbidden = true; //If the input is not one of the chars in the array exclusive_answers

	if (is_yes_no_question) { //If the input is answering a yes/no question
		for (int i = 0; i < exclusive_answers.size(); i++) { //cycle through the array of acceptable answers
			if (input == exclusive_answers[i]) { //if the input is one of the accepted answers
				input_is_forbidden = false;		 //then it is not_forbidden
			}
		}
		if (input_is_forbidden) { //If the input is not one of the accepted answers do the same stuff as aboe
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error with input. Please Try Again: ";
			goto failed_input; //restart function for new input (no assurances it will pass the first while loop)
		}
	}

	return input;
}

#endif
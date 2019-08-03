#include <iostream>
#include "global.h"

template <typename T>

void get_input(T& value) {
	std::cin >> value;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << ERROR_INVALID_INPUT << std::endl;
		std::cin >> value;
	}
}
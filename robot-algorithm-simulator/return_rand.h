#pragma once
#ifndef RETURN_RAND_H
#define RETURN_RAND_H

#include "rmas6219.h"
#include <cstdlib>
#include <ctime>

double return_rand(int max, double min) {
	srand(time(0));
	double random_num = (rand() % max) + min;
	return random_num;
}

#endif RETURN_RAND_H

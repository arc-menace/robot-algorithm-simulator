#pragma once
#ifndef RETURN_RAND_H
#define RETURN_RAND_H

#include <cstdlib>
#include <ctime>

template <typename var_type> var_type return_rand(var_type max, var_type min) {
	srand(time(0));
	var_type random_num = (rand() % max) + min;
	return random_num;
}

#endif RETURN_RAND_H

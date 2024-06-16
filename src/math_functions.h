#pragma once
#include <random>

unsigned int randint(unsigned int lower, unsigned int upper) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(lower, upper);
	return dist6(rng);
}

unsigned int round_divide(int a, int b) {
	double doub_result = (a * 1.0) / (b * 1.0);
	unsigned int int_result = a / b;
	if (doub_result < int_result + 0.5) {
		return int_result;
	}
	else {
		return int_result + 1;
	}
}
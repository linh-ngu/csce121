#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range
	return (10 <= a and a <= b and b < 10000);
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	int prevDigit = number % 10; //1
	int nextDigit = number / 10 % 10; //10

	char direction;
	
	if (nextDigit < prevDigit) {
		direction = 'M';
	} else if (nextDigit > prevDigit) {
		direction = 'V';
	} else {
		return 'N';
	}

	number /= 100;

	while (number != 0) {
		prevDigit = nextDigit; //10 2
		nextDigit = number % 10; //100s 1

		if (nextDigit == prevDigit) {
			return 'N';
		} else if (nextDigit < prevDigit && direction == 'V') {
			direction = 'M';
		} else if ((nextDigit < prevDigit) && (direction != 'V')) {
			return 'N';
		} else if (nextDigit > prevDigit && direction == 'M') {
			direction = 'V';
		} else if (nextDigit > prevDigit && direction != 'M') {
			return 'N';
		}

		number /= 10;
	}

	return direction;
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
	int mountain = 0, valley = 0, neither = 0;

	for (int i = a; i <= b; i += 1) {
		if (classify_mv_range_type(i) == 'M') {
			mountain += 1;
		} else if (classify_mv_range_type(i) == 'V') {
			valley += 1;
		} else {
			neither += 1;
		}
	}
	cout << "There are " << mountain << " mountain ranges and " << valley << " valley ranges between " << a <<  " and " << b << "." << endl;
}
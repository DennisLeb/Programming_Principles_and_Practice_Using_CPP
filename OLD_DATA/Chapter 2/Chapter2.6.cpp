// Date 22/12/2025
// File Chapter2.6.cpp
// Exercises

// [8] Write a program to test whether an input integer value is even or odd.

#include "PPPheaders.h"

int evenOrOdd() {

	int val;

	cout << "Please enter a whole number value to test: ";
	cin >> val;
	cout << '\n';

	if (val % 2 == 0) {
		cout << "Your entered value " << val << " is even.\n";
	}
	else {
		cout << "Your entered value " << val << " is odd.\n";
	}

	return 0;
}

// Date 22/12/2025
// File Chapter2.3.cpp
// Exercises

// [4] Write a program that takes in two values from the user and performs a number of operations on them.
// [5] Modify the program to take in two floating-point values and compare the results for matching inputs.

// One difference between the two (for an input of whole numbers) is this:
// The integer part of the program performs integer division, leaving you with a remainder, that can be accessed using the mod operator (%).
// The double part performs an exact division, outputting a floating-point result.
// While both data types accept int type values, only the latter half knows what to do with floating-point values.
// If you enter floating-point numbers into the first portion, the whole program will crash.

#include "PPPheaders.h"

static int intAndDoubleMath() {

	int val1, val2;

	cout << "Please enter two whole numbers (separated by one space): ";
	cin >> val1 >> val2;
	cout << '\n';

	if (val1 < val2) {
		cout << val1 << " is smaller than " << val2 << ".\n";
	}
	else if (val1 > val2) {
		cout << val1 << " is greater than " << val2 << ".\n";
	}
	else {
		cout << val1 << " is equal to " << val2 << ".\n";
	}

	cout << "The sum of " << val1 << " and " << val2 << " equals: " << val1 + val2 << ".\n";
	cout << "The difference of " << val1 << " and " << val2 << " equals: " << val1 - val2 << ".\n";
	cout << "The product of " << val1 << " and " << val2 << " equals: " << val1 * val2 << ".\n";
	cout << "The quotient of " << val1 << " and " << val2 << " equals: " << val1 / val2;
	cout << ", with a remainder of: " << val1 % val2 << ".\n\n\n";
	
	double dVal1, dVal2;

	cout << "Please enter two floating-point numbers (separated by one space): ";
	cin >> dVal1 >> dVal2;
	cout << '\n';

	if (dVal1 < dVal2) {
		cout << dVal1 << " is smaller than " << dVal2 << ".\n";
	}
	else if (dVal1 > dVal2) {
		cout << dVal1 << " is greater than " << dVal2 << ".\n";
	}
	else {
		cout << dVal1 << " is equal to " << dVal2 << ".\n";
	}

	cout << "The sum of " << dVal1 << " and " << dVal2 << " equals: " << dVal1 + dVal2 << ".\n";
	cout << "The difference of " << dVal1 << " and " << dVal2 << " equals: " << dVal1 - dVal2 << ".\n";
	cout << "The product of " << dVal1 << " and " << dVal2 << " equals: " << dVal1 * dVal2 << ".\n";
	cout << "The quotient of " << dVal1 << " and " << dVal2 << " equals: " << dVal1 / dVal2 << ".\n\n";

	return 0;
}

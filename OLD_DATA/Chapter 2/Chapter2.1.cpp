// Date 22/12/2025
// File Chapter2.1.cpp
// Exercises

// [1] siehe (...)\Programming Principles and Practice Using C++\Drills\OLD_DATA

// [2] Write a program that converts miles to kilometers.

#include "PPPheaders.h"

static int mileConverter() {

	double miles;

	cout << "***\tMile to Kilometer Converter\t***\n\n";
	cout << "Enter a distance in miles that you would like to have converted into kilometers: ";
	cin >> miles;
	cout << '\n';

	if (miles <= 0) {
		simple_error("Invalid input!");
	}
	else if (miles == 1) {
		cout << miles << " mile is equal to " << miles * 1.609 << " kilometers.\n";
	}
	else {
		cout << miles << " miles are equal to " << miles * 1.609 << " kilometers.\n";
	}

	return 0;
}

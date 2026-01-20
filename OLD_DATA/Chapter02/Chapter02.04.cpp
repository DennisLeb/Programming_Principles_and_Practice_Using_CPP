// Date 22/12/2025
// File Chapter02.04.cpp
// Exercises

// [6] Write a program that takes in three whole numbers and puts them back out sorted numerically.

#include "PPPheaders.h"

int main() {

	int val1, val2, val3;

	cout << "Please enter three whole numbers (separated by one space each): ";
	cin >> val1 >> val2 >> val3;

	if (val1 <= val2 && val1 <= val3) {
		cout << val1 << ", ";

		if (val2 < val3) {
			cout << val2 << ", " << val3;
		}
		else {
			cout << val3 << ", " << val2;
		}
	}
	else if (val2 <= val1 && val2 <= val3) {
		cout << val2 << ", ";

		if (val1 < val3) {
			cout << val1 << ", " << val3;
		}
		else {
			cout << val3 << ", " << val1;
		}
	}
	else {
		cout << val3 << ", ";

		if (val1 < val2) {
			cout << val1 << ", " << val2;
		}
		else {
			cout << val2 << ", " << val1;
		}
	}
	cout << '\n';

	return 0;
}

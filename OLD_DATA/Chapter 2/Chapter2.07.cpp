// Date 22/12/2025
// File Chapter2.07.cpp
// Exercises

// [9] Write a program that converts strings of numbers ("one", "two", etc.) into the int value of that number and outputs it.

#include "PPPheaders.h"

int main() {

	string numString;

	cout << "Please enter a spelled-out number between zero and four: ";
	cin >> numString;
	cout << '\n';

	if (numString == "zero" || numString == "Zero") {
		cout << "You entered 0!";
	}
	else if (numString == "one" || numString == "One") {
		cout << "You entered 1!";
	}
	else if (numString == "two" || numString == "Two") {
		cout << "You entered 2!";
	}
	else if (numString == "three" || numString == "Three") {
		cout << "You entered 3!";
	}
	else if (numString == "four" || numString == "Four") {
		cout << "You entered 4!";
	}
	else {
		cout << "Not a number I know :(";
	}
	cout << '\n';

	return 0;
}

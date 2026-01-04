// 25/12/2025
// Chapter3.1.cpp
// Exercises

// [1] Write a program that reads a string from input and then, for each character read, prints out that character and its integer value.

#include "PPPheaders.h"

int main() {

	string inpStr;

	cout << "Please enter a string: ";
	cin >> inpStr;
	cout << '\n';

	for (char i : inpStr) {
		cout << "Character: " << i << '\t';
		cout << "Integer value: " << int(i) << '\n';
	}

	return 0;
}

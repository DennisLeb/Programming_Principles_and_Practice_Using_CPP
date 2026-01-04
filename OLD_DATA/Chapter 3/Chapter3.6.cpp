// 26/12/2025
// Chapter3.6.cpp
// Exercises

// [7] Make a vector that holds the spelled-out numbers from 1 to 9 as strings. Write a program that converts the input of a number as an int to its string and vice versa.

#include "PPPheaders.h"

int main() {

	vector<string> strNums = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	string strInput;

	cout << "Please enter a number from 1 to 9 either spelled-out or as an integer: ";
	cin >> strInput;
	cout << '\n';

	// if 0-9
	if ((int)strInput[0] >= 48 && (int)strInput[0] <= 57) {

		// Convert ASCII digit into int of same value
		int intInput = (int)strInput[0] - 48;

		cout << "You entered \'" << intInput << "\' which, as a string, would look like this: " << strNums[intInput] << ".\n";
		return 0;
	}
	else {

		// Allows for uppercase input
		for (auto& x : strInput)
			x = tolower(x);

		for (int i = 0; i < strNums.size(); i++) {
			if (strInput == strNums[i]) {
				cout << "You entered \"" << strInput << "\" which, as an integer, would look like this: " << i << ".\n";
				return 0;
			}
		}
	}
	cout << "Input not recognized!\n";
	return 0;
}

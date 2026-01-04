// 26/12/2025
// Chapter3.07.cpp
// Exercises

// [8] Modify the "mini calculator" from exercise [6] to accept (just) single-digit numbers written as either digits or spelled out.

#include "PPPheaders.h"


int stringToInt(string strInput) {

	vector<string> strNums = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

	// Is it a digit?
	if ((int)strInput[0] >= 48 && (int)strInput[0] <= 57) {

		// Convert ASCII digit into int of same value
		int intInput = (int)strInput[0] - 48;

		return intInput;
	}
	else {

		// Allows for uppercase input
		for (auto& x : strInput)
			x = tolower(x);

		for (int i = 0; i < strNums.size(); i++) {
			if (strInput == strNums[i]) {
				return i;
			}
		}
	}
	simple_error("Input not recognized!");
}

int main() {

	string val1, val2;
	char op;

	cout << "Please enter a mathematical operation using two single digit values, either spelled-out or as an integer, and a basic arithmetic operator (i.e. x + y): ";
	cin >> val1 >> op >> val2;
	cout << '\n';

	int intVal1 = stringToInt(val1);
	int intVal2 = stringToInt(val2);
	
	if (op == '+') {
		cout << "The sum of " << intVal1 << " and " << intVal2 << " is " << intVal1 + intVal2;
	}
	else if (op == '-') {
		cout << "The difference between " << intVal1 << " and " << intVal2 << " is " << intVal1 - intVal2;
	}
	else if (op == '*') {
		cout << "The product of " << intVal1 << " and " << intVal2 << " is " << intVal1 * intVal2;
	}
	else if (op == '/') {
		cout << "The quotient of " << intVal1 << " and " << intVal2 << " is " << intVal1 / intVal2;
	}
	else {
		simple_error("Invalid input!");
	}
	cout << '\n';

	return 0;
}

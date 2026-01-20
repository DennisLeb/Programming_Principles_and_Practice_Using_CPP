// Date 22/12/2025
// File Chapter02.08.cpp
// Exercises

// [10] Build a basic calculator for the following operators: +, -, *, /.

#include "PPPheaders.h"

int main() {

	string operation;
	double val1, val2;

	cout << "Please enter your desired operator (+ or plus, - or minus, * or mul, / or div): ";
	cin >> operation;
	cout << "Please enter your two desired floating-point operands (separated by one space): ";
	cin >> val1 >> val2;
	cout << '\n';

	if (operation == "+" || operation == "plus") {
		cout << val1 << ' ' << operation << ' ' << val2 << " equals " << val1 + val2 << ".\n";
	}
	else if (operation == "-" || operation == "minus") {
		cout << val1 << ' ' << operation << ' ' << val2 << " equals " << val1 - val2 << ".\n";
	}
	else if (operation == "*" || operation == "mul") {
		cout << val1 << " multiplied by " << val2 << " equals " << val1 * val2 << ".\n";
	}
	else if (operation == "/" || operation == "div") {
		cout << val1 << " divided by " << val2 << " equals " << val1 / val2 << ".\n";
	}
	else {
		simple_error("Invalid input!");
	}

	return 0;
}

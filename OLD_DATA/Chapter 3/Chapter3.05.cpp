// 25/12/2025
// Chapter3.05.cpp
// Exercises

// [6] Write a program that performs as a very simple calculator. It should take three arguments from the user: two double values as operands and one of the four basic arithmetic operators.           

#include "PPPheaders.h"

int main() {

	double val1, val2;
	char op;

	cout << "Please enter a mathematical operation using two floating-point values and a basic arithmetic operator (i.e. x + y): ";
	cin >> val1 >> op >> val2;
	cout << '\n';

	if (op == '+') {
		cout << "The sum of " << val1 << " and " << val2 << " is " << val1 + val2;
	}
	else if (op == '-') {
		cout << "The difference between " << val1 << " and " << val2 << " is " << val1 - val2;
	}
	else if (op == '*') {
		cout << "The product of " << val1 << " and " << val2 << " is " << val1 * val2;
	}
	else if (op == '/') {
		cout << "The quotient of " << val1 << " and " << val2 << " is " << val1 / val2;
	}
	else {
		simple_error("Invalid input!");
	}
	cout << '\n';

	return 0;
}

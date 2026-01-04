// 03/01/2026
// Chapter3.15.cpp
// Exercises

// [17] Write a program to solve quadratic equations. Use doubles for user input a, b, and c and output all solutions.

#include "PPPheaders.h"

int main() {

	double inp_a, inp_b, inp_c, sol_1, sol_2;

	cout << "Please enter three values (a, b, c) to insert into the quadratic equation: ";
	cin >> inp_a >> inp_b >> inp_c;
	cout << '\n';

	// First using the discriminant to find the number of solutions
	double discriminant = inp_b * inp_b - 4 * inp_a * inp_c;	// D = b^2 - 4ac

	// Calculating each solution or none at all
	if (discriminant > 0 /* Two solutions */) {
		sol_1 = (-inp_b + sqrt(inp_b * inp_b - 4 * inp_a * inp_c)) / (2 * inp_a);
		sol_2 = (-inp_b - sqrt(inp_b * inp_b - 4 * inp_a * inp_c)) / (2 * inp_a);

		cout << "Your input values have two solutions!\n\n";
		cout << "x1 = " << sol_1 << '\n';
		cout << "x2 = " << sol_2 << '\n';
	}
	else if (discriminant == 0 /* One solution */) {
		sol_1 = (-inp_b + sqrt(inp_b * inp_b - 4 * inp_a * inp_c)) / (2 * inp_a);

		cout << "Your input values have one solution!\n\n";
		cout << "x = " << sol_1 << '\n';
	}
	else /* No solutions */ {
		cout << "Your input values do not have any solution!\n";
	}
	
	return 0;
}

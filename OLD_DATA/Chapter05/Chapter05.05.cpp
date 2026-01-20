// 20/01/2026
// Chapter05.05.cpp
// Exercises

// [8] Design a program that asks users to enter two numbers, asks them whether they want to calculate permutations or combinations, and prints out the results.

#include "PPPheaders.h"

// asks for input until correct
int getInt() {

	int x = 0;
	while (true) {
		if (!(cin >> x) || x < 0) {
			cin.clear();
			cin.ignore();
			cerr << "bad input, try again!\n";
			continue;
		}
		return x;
	}
}
// calculates factorials
int factorial(int x) {

	if (x < 0)
		error("negative factorial");
	if (x > 15)
		error("factorial range");
	if (x == 0)
		return 1;

	for (int i = x - 1; i > 0; i--)
		x *= i;
	return x;
}
// calculates permutation
int getPermutation(int a, int b) {

	int x = factorial(a) / factorial(a - b);

	return x;
}
// calculates combination
int getCombination(int a, int b, int P) {

	int x = P / factorial(b);

	return x;
}
// calculates result based on arguments
int getResult(int a, int b, int op) {

	int x = getPermutation(a, b);
	if (op == 1)
		return x;

	x = getCombination(a, b, x);
	return x;
}

int main() {

	int a = 0, b = 0, op = 0, res = 0;

	try {
		cout << "Enter non-negative integer a-value >> ";
		a = getInt();
		cout << "Enter non-negative integer b-value >> ";
		b = getInt();
		cout << "Do you want to calculate 1.Permutation or 2.Combinaton? (1/2) >> ";
		op = getInt();
		while (op != 1 && op != 2) {
			cerr << "bad input, try again!\n";
			op = getInt();
		}
		
		res = getResult(a, b, op);

		switch (op) {
		case 1:
			cout << "\nThere are " << res << " Permutations for your values.\n";
			return 0;
		case 2:
			cout << "\nThere are " << res << " Combinations for your values.\n";
			return 0;
		default:
			error("unexpected op");
		}
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "unknown error" << '\n';
		return 2;
	}
}

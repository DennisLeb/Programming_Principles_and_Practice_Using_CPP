// 07/01/2025
// Chapter04.05.cpp
// Exercises

// [11] Write a program that writes out the first n values of the Fibonacci series. Find the largest Fibonacci number that fits in an int.
// Answer: The largest Fibonacci number that fits is: 1.836.311.903. It is 46th in the Fibonacci series.

#include "PPPheaders.h"

vector<int> findFibNums(int n) {

	int new_num;
	vector<int> fib_nums;

	for (int i = 0; i < n; i++) {
		// Calculates next fib_num from the last two
		if (i > 1) {
			// Checks whether int would overflow
			if (fib_nums[i - 1] > INT_MAX - fib_nums[i - 2])
				error("fib_nums: int overflow");
			
			new_num = fib_nums[i - 2] + fib_nums[i - 1];
		}
		// else if there are no last two
		else
			new_num = 1;

		fib_nums.push_back(new_num);
	}

	return fib_nums;
}

int main() {

	int n_amt;
	vector<int> fib_nums;

	try {
		cout << "Please enter how many Fibonacci numbers you'd like written out: ";
		cin >> n_amt;
		cout << '\n';

		if (cin.fail() || n_amt <= 0)
			error("n_amt: invalid input");

		fib_nums = findFibNums(n_amt);
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
		return 1;
	}

	for (auto x : fib_nums) {
		cout << x << '\n';
	}

	return 0;
}

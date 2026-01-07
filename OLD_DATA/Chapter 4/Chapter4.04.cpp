// 07/01/2025
// Chapter4.04.cpp
// Exercises

// [8] Write a program that reads and stores a series of integers and then computes the sum of the first n values. First ask for n.
// [9] Modify the program to write out an error if the result cannot be represented as an int.
// [10] Modify the program to use double instead of int. Also make a double vector filled with the differences between adjacent nums values. Write out that vector of differences.

#include "PPPheaders.h"

int main() {

	int n_amt;
	double new_num, res = 0;
	vector<double> nums;
	vector<double> diffs;

	try {
		cout << "Please enter the number of elements you'd like to add up: ";
		cin >> n_amt;
		if (cin.fail() || n_amt <= 0)
			error("invalid input: n_amt");
	
		cout << "\nNow please enter a series of doubles: ";
		while (cin >> new_num) {
			if (cin.fail())
				error("invalid input: nums");
			nums.push_back(new_num);
		}
		cout << '\n';
		
		if (n_amt > nums.size())
			error("requested n is greater than number of entered doubles");

		for (int i = 0; i < n_amt; i++) {

			// Checks if res + nums[i] would overflow (res > DBL_MAX)
			if (res > 0 && nums[i] > DBL_MAX - res)
				error("res: double overflow");
			// Checks if res + nums[i] would underflow (res < DBL_MIN)
			if (res < 0 && nums[i] < DBL_MIN - res)
				error("res: double underflow");

			res += nums[i];
		}
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
		return 1;
	}

	for (int i = 0; i < n_amt - 1; i++) {
		new_num = nums[i] - nums[i + 1];
		diffs.push_back(new_num);
		//cout << "difference #" << i + 1 << ": " << nums[i] << " - " << nums[i + 1] << " == " << new_num << '\n';
	}
	for (auto x : diffs)
		cout << x << '\n';

	cout << "\nThe sum of the first " << n_amt << " doubles is: " << res << ".\n";

	return 0;
}

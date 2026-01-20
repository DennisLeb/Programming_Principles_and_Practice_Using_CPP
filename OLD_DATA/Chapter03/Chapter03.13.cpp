// 02/01/2026
// Chapter03.13.cpp
// Exercises

// [15] Write a program that finds the mode of a set of positive integers. A mode is a number that appears the most times in a sequence.

#include "PPPheaders.h"

int findMode(vector<int> nums) {

	int size = nums.size(), most_reps = 0;

	// Vector to compare repetitions
	vector<int> num_rep_vec(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

			// Prevents comparison of the same input
			if (i == j)
				continue;

			// Uses index to link value and repetitions
			if (nums[i] == nums[j])
				num_rep_vec[i]++;
		}

		if (num_rep_vec[i] > most_reps) {
			most_reps = i;
		}
	}

	return nums[most_reps];
}

int main() {

	int new_num;
	vector<int> nums;
	cout << "Please enter a sequence of positive integers (max. 50): ";

	while (cin >> new_num) {
		if (new_num <= 0) {
			cout << "\nInvalid input: " << new_num << "; ignored\n";
			continue;
		}
		if (nums.size() > 50)
			simple_error("Too many inputs!");

		nums.push_back(new_num);
	}

	int mode = findMode(nums);

	cout << "\nThe mode of that sequence is: " << mode << "!\n";

	return 0;
}

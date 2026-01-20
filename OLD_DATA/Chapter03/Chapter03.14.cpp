// 02/01/2026
// Chapter03.14.cpp
// Exercises

// [16] Write a program that finds the min, max and mode of a sequence of strings

#include "PPPheaders.h"

int main() {

	string new_string;
	vector<string> strings;
	cout << "Please enter a sequence of strings (max. 50): ";

	while (cin >> new_string) {
		if (strings.size() > 50)
			simple_error("Too many inputs!");

		strings.push_back(new_string);
	}
	if (strings.size() == 0)
		simple_error("No Input!");

	int size = strings.size(), most_reps = 0;

	// Vector to compare repetitions
	vector<int> string_rep_vec(size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

			// Prevents comparison of the same input
			if (i == j)
				continue;

			// Uses index to link value and repetitions
			if (strings[i] == strings[j])
				string_rep_vec[i]++;
		}

		if (string_rep_vec[i] > most_reps) {
			most_reps = i;
		}
	}
	string mode = strings[most_reps];
	ranges::sort(strings);

	cout << "\nMode: " << mode;
	cout << "\nMin: " << strings[0];
	cout << "\nMax: " << strings[size - 1] << '\n';

	return 0;
}

// Note that I would have written a separate function to find mode, just as in the previous exercise, but there's a problem with using
// an object of type vector<string> as a function parameter with the PPPheaders.h definition. I don't really understand why that is yet, so I'll just avoid it.

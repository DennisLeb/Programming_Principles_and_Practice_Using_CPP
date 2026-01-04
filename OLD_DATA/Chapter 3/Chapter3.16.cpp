// 03/01/2026
// Chapter3.16.cpp
// Exercises

// [18] Write a program where a user first enters a set of name-and-value pairs, such as Joe 17. Add them to a vector and make sure each name is unique.
// [19] Modify the program to repeatedly ask a user for a name, in order to output the according score.
// [20] Modify the program to repeatedly ask a user for a score, in order to output the according names.

#include "PPPheaders.h"

int main() {

	string new_name;
	int new_score;

	vector<string> names;
	vector<int> scores;

	cout << "Please enter a set of pairs such as \"Joe 17\" (terminate input by typing \"NoName\" as the name or '0' as the score): ";

	while (cin >> new_name >> new_score) {
		if (new_name == "NoName" || new_score == 0)
			break;

		names.push_back(new_name);
		scores.push_back(new_score);
	}
	size_t size = names.size();

	for (int i = 0; i < size; i++) {
		cout << '\n';

		for (int j = 0; j < size; j++) {
			if (i == j)
				continue;
			
			if (names[i] == names[j])
				simple_error("Found identical name!");
		}
		cout << "Name #" << i + 1 << ": " << names[i] << '\n';
		cout << "Score #" << i + 1 << ": " << scores[i] << '\n';
	}

	do {
		cout << "\nEnter one of the scores to access the names with that score (terminate input by typing \"NoName\"): ";
		cin >> new_name;
		cout << '\n';

		for (int i = 0; i < size; i++) {
			if (new_name == names[i]) {
				cout << "That name's score is: " << scores[i] << '\n';
				break;
			}
			if (i == size - 1 && new_name != "NoName")
				cout << "Name not found!\n";
		}
	} while (new_name != "NoName");
	
	do {
		cout << "\nEnter one of the names to access its score (terminate input by typing '0'): ";
		cin >> new_score;
		cout << '\n';

		for (int i = 0; i < size; i++) {
			if (new_score == scores[i])
				cout << "Name(s) with that score: " << names[i] << '\n';
			else if (i == size - 1 && new_score != 0)
				cout << "Score not found!\n";
		}
	} while (new_score != 0);

	return 0;
}

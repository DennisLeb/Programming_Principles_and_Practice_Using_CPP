// 20/01/2026
// Chapter05.02.cpp
// Exercises

// [4] Rework exercise 20 in Chapter 3 to use a vector<Name_value> instead of two vectors. Define a class Name_value that holds a string and a value.

#include "PPPheaders.h"

class Name_value {

public: 
	string name;
	int score;
};

int main() {

	Name_value new_entry;
	vector<Name_value> name_val_vec;

	cout << "Please enter a set of pairs such as \"Joe 17\" (terminate input by typing \"NoName\" as the name or '0' as the score): ";

	while (cin >> new_entry.name >> new_entry.score) {
		if (new_entry.name == "NoName" || new_entry.score == 0)
			break;

		name_val_vec.push_back(new_entry);
	}
	size_t size = name_val_vec.size();

	for (int i = 0; i < size; i++) {
		cout << '\n';

		for (int j = 0; j < size; j++) {
			if (i == j)
				continue;

			if (name_val_vec[i].name == name_val_vec[j].name) {
				cerr << "Found identical name!";
				exit(1);
			}
		}
		cout << "Name #" << i + 1 << ": " << name_val_vec[i].name << '\n';
		cout << "Score #" << i + 1 << ": " << name_val_vec[i].score << '\n';
	}

	do {
		cout << "\nEnter one of the names to access its score (terminate input by typing \"NoName\"): ";
		cin >> new_entry.name;
		cout << '\n';

		for (int i = 0; i < size; i++) {
			if (new_entry.name == name_val_vec[i].name) {
				cout << "That name's score is: " << name_val_vec[i].score << '\n';
				break;
			}
			if (i == size - 1 && new_entry.name != "NoName")
				cout << "Name not found!\n";
		}
	} while (new_entry.name != "NoName");

	do {
		cout << "\nEnter one of the scores to access the names with that score (terminate input by typing '0'): ";
		cin >> new_entry.score;
		cout << '\n';

		for (int i = 0; i < size; i++) {
			if (new_entry.score == name_val_vec[i].score)
				cout << "Name(s) with that score: " << name_val_vec[i].name << '\n';
			else if (i == size - 1 && new_entry.score != 0)
				cout << "Score not found!\n";
		}
	} while (new_entry.score != 0);

	return 0;
}

// vladimir 69 opa 7 epischmeister 45 hallihallo 01 oma 7
// 01/02/2026
// Chapter07.06.cpp
// Exercises

//
// [7] Read five names into a vector<string> name, then prompt the user for the ages of the people named and store them in a vector<double> age. Print out the five pairs.
//     Then sort the names (sort(name.begin(), name.end())) and print out the sorted pairs.
//
// [8] Modify the program to allow an arbitrary number of names.
//

#include "PPPheaders.h"

const string quitKey = "quit";

void getInput(vector<string>& name) {

	string new_name;
	cout << "Enter some unique names (end input by typing \"" << quitKey << "\") > ";
	while (true) {
		cin >> new_name;
		if (cin.fail())
			error(new_name, " is an invalid input");
		if (new_name == quitKey)
			break;
		name.push_back(new_name);
	}
	cout << endl;
	// checks for identical names
	for (int i = 0; i < name.size(); i++) {
		for (int j = 0; j < name.size(); j++) {
			if (i == j)
				continue;
			if (name[i] == name[j])
				error(name[i], " is not a unique name");
		}
	}
	return;
}

void getInput(vector<double>& age, const int& vec_size) {

	double new_age = 0;
	cout << "Enter one age per name (" << vec_size << " values) > ";
	while ((int)age.size() < vec_size) {
		cin >> new_age;
		if (cin.fail() || new_age < 0)
			error("invalid age input");
		age.push_back(new_age);
	}
	cout << endl;
	return;
}

// sorts age vector elements using the index of matching names
void sortAge(vector<double>& age, const vector<string>& sorted_name, const vector<string>& name) {

	int size = name.size();
	vector<double> sorted_age(size);	// separate vector to avoid assigning already reassigned ages

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (name[i] == sorted_name[j]) {
				sorted_age[j] = age[i];
				break;
			}
		}
	}
	age = sorted_age;
	return;
}

// prints each vec element with label
void print(const string& label, const vector<string>& name, const vector<double>& age) {

	for (int i = 0; i < name.size(); i++)
		cout << label << " #" << i + 1 << '\t' << name[i] << ", " << age[i] << endl;
	cout << endl;
	return;
}

int main() {

	try {
		vector<string> name;
		vector<double> age;
		getInput(name);
		getInput(age, (int)name.size());
		print("Pair", name, age);

		vector<string> name_copy = name;	// create copy of name before sorting to order age correctly
		ranges::sort(name);
		sortAge(age, name, name_copy);
		print("Sorted Pair", name, age);

		return 0;
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown error";
		return 2;
	}
}

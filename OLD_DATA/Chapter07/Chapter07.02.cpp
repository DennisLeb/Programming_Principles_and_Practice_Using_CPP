// 31/01/2026
// Chapter07.02.cpp
// Exercises

//
// [2] Write a function print() that prints a vector of ints to cout. Give it two arguments: a string for "labeling" the output and a vector.
//

#include "PPPheaders.h"

// fills int vector of random size (1-50) with random ints (0-100)
void fillVec(vector<int>& vec) {

	seed((unsigned int)time(NULL));
	int vec_size = random_int(1, 50);

	for (int i = 0; i < vec_size; i++)
		vec.push_back(random_int(100));

	return;
}

// prints each vec element with label
void print(const string& label, const vector<int>& vec) {

	for (int i = 0; i < vec.size(); i++)
		cout << label << " #" << i + 1 << '\t' << vec[i] << endl;
}

int main() {

	try {
		vector<int> vec;
		fillVec(vec);
		print("Element", vec);
		return 0;
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown error\n";
		return 2;
	}
}

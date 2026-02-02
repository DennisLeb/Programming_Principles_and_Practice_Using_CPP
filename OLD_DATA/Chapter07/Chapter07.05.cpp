// 01/02/2026
// Chapter07.05.cpp
// Exercises

//
// [5] Write versions of the functions in ex 5, but with a vector<string>.
//

#include "PPPheaders.h"

// reverses order using new vector
void reverseFunc1(const vector<string>& vec, vector<string>& revVec) {

	for (int i = vec.size() - 1; i >= 0; i--)
		revVec.push_back(vec[i]);

	return;
}

// reverses order using index reversal
void reverseFunc2(vector<string>& vec) {

	for (int i = 0; i < ((int)vec.size() / 2); i++) {	// reverses indices until it reaches vector middle (making good use of int division)
		int revIndex = abs(i - ((int)vec.size() - 1));	// new index = absolute value of current_i - max_i
		swap(vec[i], vec[revIndex]);
	}
	return;
}

// prints each vec element with label
void print(const string& label, const vector<string>& vec) {

	for (int i = 0; i < vec.size(); i++)
		cout << label << " #" << i + 1 << '\t' << vec[i] << endl;
	return;
}

int main() {

	try {
		vector<string> vec{ "Hello", "World", "These", "Are", "Some", "Strings", "That", "I", "Came", "Up", "With"};
		bool use_func1 = false;		// change to test func 1 or 2

		if (use_func1) {
			vector<string> revVec;
			reverseFunc1(vec, revVec);
			print("Element", revVec);
		}
		else {
			reverseFunc2(vec);
			print("Element", vec);
		}
		return 0;
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown error" << endl;
		return 2;
	}
}

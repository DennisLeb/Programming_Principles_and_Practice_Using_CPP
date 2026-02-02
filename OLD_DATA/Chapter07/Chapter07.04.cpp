// 01/02/2026
// Chapter07.04.cpp
// Exercises

//
// [5] Write two functions that reverse the order of elements in a vector<int>.
//     The first should produce a new vector with the reversed sequence, leaving its original vector unchanged.
//     The other reverse function should reverse the elements of its vector without using any other vectors (hint: swap()).
//

#include "PPPheaders.h"

// reverses order using new vector
void reverseFunc1(const vector<int>& vec, vector<int>& revVec) {

	for (int i = vec.size() - 1; i >= 0; i--) 
		revVec.push_back(vec[i]);
	
	return;
}

// reverses order using index reversal
void reverseFunc2(vector<int>& vec) {

	for (int i = 0; i < ((int)vec.size() / 2); i++) {	// reverses indices until it reaches vector middle (making good use of int division)
		int revIndex = abs(i - ((int)vec.size() - 1));	// new index = absolute value of current_i - max_i
		swap(vec[i], vec[revIndex]);
	}
	return;
}

// prints each vec element with label
void print(const string& label, const vector<int>& vec) {

	for (int i = 0; i < vec.size(); i++)
		cout << label << " #" << i + 1 << '\t' << vec[i] << endl;
	return;
}

int main() {

	try {
		vector<int> vec{ 1, 3, 5, 7, 9, 11, 13, 15 };
		bool use_func1 = false;		// change to test func 1 or 2

		if (use_func1) {
			vector<int> revVec;
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

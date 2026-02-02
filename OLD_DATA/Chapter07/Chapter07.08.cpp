// 02/02/2026
// Chapter07.08.cpp
// Exercises

//
// [12] Improve print_until_s() from §7.4.2 and test it. Give reasons for what makes a good set of test cases.
//      Then, write a print_until_ss() that prints until it sees a second occurrence of its quit argument.
//
//      Improvements:
//          - quit keyword is now a constant
//          - now checks if vec is empty
//          - now passing vec by const-reference
//		Ans:
//			Good test cases are written with the intent of finding specific exploits or missed edge cases, they're not just random values.
//			When looking for test cases you need to be looking for ways to outsmart your own program.
//

#include "PPPheaders.h"
#define QUIT "quit"

// print until the string called "quit" is found
void print_until_s(const vector<string>& vec, string quit) {

	if (vec.size() == 0)
		error("empty vector passed to print_until_s()");

	for (string s : vec) {
		if (s == quit)
			return;
		cout << s << endl;
	}
	return;
}

// print until the string called "quit" is found twice
void print_until_ss(const vector<string>& vec, string quit) {

	if (vec.size() == 0)
		error("empty vector passed to print_until_ss()");

	int quit_ctr = 0;
	for (string s : vec) {
		if (s == quit) {
			quit_ctr++;
			if (quit_ctr == 2)
				return;
			continue;
		}
		cout << s << endl;
	}
	return;
}

int main() {

	try {
		vector<string> vec{ "Hello", "World", "These", "Are", "Some", "Strings", QUIT, "That", "I", "Came", QUIT, "Up", "With" };
		print_until_ss(vec, QUIT);
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

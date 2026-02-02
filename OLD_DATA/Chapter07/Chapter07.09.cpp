// 02/02/2026
// Chapter07.09.cpp
// Exercises

//
// [13] Write a function that takes a vector<string> argument and returns a vector<int>, containing the number of characters in each string.
//      Also find the longest and the shortest string and the lexicographically first and last string.
//		How many separate functions would you use for these tasks. Why?
//
//		Ans:
//			Using only one function to return the vector<int> and assign everything else is simplest and the most efficient option.
//			It requires only one for loop to get the data I needed. This in combination with the struct constructor made the code look quite nice, I think.
//

#include "PPPheaders.h"

struct vec_properties {
public:
	vec_properties(const vector<string>& vec) { num_of_chars = getVecProperties(vec); };

	vector<int> num_of_chars;
	string longest;
	string shortest;
	string lex_first;
	string lex_last;

private:
	// returns num_of_chars and assigns all other variables
	vector<int> getVecProperties(const vector<string>&);
};

vector<int> vec_properties::getVecProperties(const vector<string>& vec) {

	if (vec.size() == 0)
		error("empty vector passed to getVecProperties()");

	vector<int> num_of_chars;		// doing this reluctantly and only because the exercise explicitly says to return a vector<int>

	// necessary for accurate comparison (longest and lex_last being empty is fine)
	shortest = vec[0];
	lex_first = vec[0];

	for (string s : vec) {
		num_of_chars.push_back(s.length());

		if (s.length() < shortest.length())
			shortest = s;
		else if (s.length() > longest.length())		// cheeky optimization using else if instead of if
			longest = s;

		if (s < lex_first)
			lex_first = s;
		else if (s > lex_last)
			lex_last = s;
	}
	return num_of_chars;
}

int main() {

	try {
		vector<string> vec{ "Hello", "World", "These", "Are", "Some", "Strings", "That", "I", "Came", "Up", "With"};
		vec_properties vec_p(vec);

		for (int i = 0; i < vec_p.num_of_chars.size(); i++)
			cout << "String #" << i + 1 << " has " << vec_p.num_of_chars[i] << " char(s)." << endl;

		cout << endl;
		cout << "The longest string is \"" << vec_p.longest << "\"." << endl;
		cout << "The shortest string is \"" << vec_p.shortest << "\"." << endl << endl;
		
		cout << "The lexicographically first string is \"" << vec_p.lex_first << "\"." << endl;
		cout << "The lexicographically last string is \"" << vec_p.lex_last << "\"." << endl;

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

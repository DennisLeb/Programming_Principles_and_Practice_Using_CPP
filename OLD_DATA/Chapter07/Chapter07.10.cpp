// 02/02/2026
// Chapter07.10.cpp
// Exercises

//
// [14] Can we declare a non-reference function argument const (e.g., void f(const int);)? What might that mean? Why might we want to do that?
//		Why don't people do that often? Try it; write a couple of small programs to see what works.
//
//		Ans:
//			Doing this will prevent you from changing the argument's value, which is unnecessary because it will create an independant copy anyways.
//			So basically you get the efficiency penalty for creating a copy, without the benefit of being able to modify the value at all.
//			It's the worst of both worlds.
//

#include "PPPheaders.h"

// still works fine
int area(const int x, const int y) { return (x * y); }

// won't compile because a const can't be an lvalue
int area2(const int x, const int y) { x *= y; return x; }

int main() {

	try {
		int x = 4, y = 10;
		vector<int> vec{ 1, 5, 7, 13, 8, 234, 6, 1, 76, 9623 };

		cout << area(x, y) << endl;
		cout << area2(x, y) << endl;
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

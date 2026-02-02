// 01/02/2026
// Chapter07.03.cpp
// Exercises

//
// [3] Create a vector of Fibonacci number to print, using the print() function from Ex 2. Do this using a function fibonacci(int x,int y,vector<int> v,int n) where
//     x will be v[0] and y will be v[1]. Use x and y to create a Fibonacci sequence of n length.
//
// [4] Find an approximation of the maximum number int can hold using fibonacci().
//     Ans:
//         For the classical Fibonacci sequence (x = 1, y = 1) element #46 is the largest number int could hold, this being 1836311903.
//		   This means the following:
//		       1836311903 < INT_MAX < 2971215073
// 
//		   with the latter number being element #47, the sum of element #45 and #46.
//

#include "PPPheaders.h"

// gets x, y and n from user
void getInput(int& x, int& y, int& n) {

	cout << "How long should your Fibonacci sequence be? (max. 40) > ";
	cin >> n;
	if (cin.fail() || n < 1 || n > 400)
		error("invalid input");

	cout << "What two numbers should your sequence start with? > ";
	cin >> x >> y;
	if (cin.fail())
		error("invalid input");
	cout << endl;
	return;
}

// fills v with custom Fibonacci sequence
void fibonacci(const int& x, const int& y, vector<int>& v, const int& n) {

	v.push_back(x);
	v.push_back(y);

	for (int i = 2; i < n; i++) {
		// Checks whether v[i - 2] + v[i - 1] would overflow
		if (v[i - 1] > INT_MAX - v[i - 2])
			error("fib_nums: int overflow");

		v.push_back(v[i - 2] + v[i - 1]);
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
		int x = 0, y = 0, n = 0;
		vector<int> v;

		getInput(x, y, n);
		fibonacci(x, y, v, n);
		print("Element", v);
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

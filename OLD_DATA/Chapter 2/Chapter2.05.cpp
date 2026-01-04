// Date 22/12/2025
// File Chapter2.05.cpp
// Exercises

// [7] Modify exercise 6 to take in string values and sort them alphabetically.

#include "PPPheaders.h"

int main() {

	string str1, str2, str3;

	cout << "Please enter three strings (separated by one space each): ";
	cin >> str1 >> str2 >> str3;

	if (str1 <= str2 && str1 <= str3) {
		cout << str1 << ", ";

		if (str2 < str3) {
			cout << str2 << ", " << str3;
		}
		else {
			cout << str3 << ", " << str2;
		}
	}
	else if (str2 <= str1 && str2 <= str3) {
		cout << str2 << ", ";

		if (str1 < str3) {
			cout << str1 << ", " << str3;
		}
		else {
			cout << str3 << ", " << str1;
		}
	}
	else {
		cout << str3 << ", ";

		if (str1 < str2) {
			cout << str1 << ", " << str2;
		}
		else {
			cout << str2 << ", " << str1;
		}
	}
	cout << '\n';

	return 0;
}

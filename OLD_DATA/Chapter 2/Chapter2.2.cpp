// Date 22/12/2025
// File Chapter2.2.cpp
// Exercises

// [3] Write a program that declares variables with some legal and some illegal names and watch your compiler react.

#include "PPPheaders.h"

int main() {

	// legal names
	string myStr = "hello ;)";
	int numOfSmth = 7;
	double favNum = 14.77;
	
	// illegal names
	int double = 70;	// Ungültige Kombination von Typspezifizierern.
	float 60 = 2.1;		// Es wurde ein Bezeichner erwartet.
	char #3 = 'f';		// "#" wurde an dieser Stelle nicht erwartet.

	return 0;
}

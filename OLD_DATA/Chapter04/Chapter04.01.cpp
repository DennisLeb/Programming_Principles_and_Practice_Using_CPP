// 06/01/2025
// Chapter04.01.cpp
// Exercises

// [2] The following code has many errors in it. Find them, list them and correct the code.
// [3] Absolute zero (-273.15C or 0K) is the lowest temperature that can be reached. Place a check in main() that will produce an error if a temperature below absolute zero is given.
// [4] Do excercise 3 again, but this time handle the error inside ctok().
// [5] Add to the program so that it can also convert Kelvin to Celsius.

#include "PPPheaders.h"

/*
double ctok(double c) {		// converts Celsius to Kelvin

	int k = c + 273.25;

	return int;
}

int main() {

	double c = 0;			// declare input variable
	cin >> d;				// retrieve temperature to input variable
	double k = ctok("c");	// convert temperature
	Cout << k << '\n';		// print out temperature
}
*/

// 1. ctok() should return k, not "int"
// 2. ctok()'s k variable should be a double
// 3. input should be stored in c, not 'd'
// 4. ctok() takes a double, not a string as a variable 
// 5. cout was misspelled
// 6. wrong conversion value. 273.25 should be 273.15
// (7. no return from main())

/* [2]/[3]
double ctok(double c) {		// converts Celsius to Kelvin

	double k = c + 273.15;

	return k;
}

int main() {

	double c = 0, k;		// declare input variable
	cin >> c;				// retrieve temperature to input variable
	
	try {
		k = ctok(c);		// convert temperature
		if (k < 0)
			error("Temperature below absolute zero!\n");
	}
	catch (exception& e) {
		cerr << e.what();
		return 1;
	}

	cout << k << '\n';		// print out temperature
	return 0;
}
*/

// [4/5]
double convertThis(char unit, double temp) {

	double res = 0;

	if (unit == 'c') {
		res = temp + 273.15;
		expect([&] {return 0 <= res;}, "Temperature below absolute zero!\n");
	}
	else if (unit == 'k') {
		res = temp - 273.15;
		expect([&] {return -273.15 <= res;}, "Temperature below absolute zero!\n");
	}
	else
		error("Unexpected unit!");


	return res;
}

int main() {

	double inp_temp, res_temp;
	char conv_char;

	cout << "Please enter a temperature followed by a unit (C or K): ";
	cin >> inp_temp >> conv_char;
	conv_char = char(tolower(conv_char));

	// Failed input or not desired unit
	if (!cin || (conv_char != 'c' && conv_char != 'k'))
		simple_error("invalid input!");
	cout << '\n';

	try {
		res_temp = convertThis(conv_char, inp_temp);
	}
	catch (exception& e) {
		cerr << e.what();
		return 1;
	}

	cout << res_temp << '\n';
	return 0;
}

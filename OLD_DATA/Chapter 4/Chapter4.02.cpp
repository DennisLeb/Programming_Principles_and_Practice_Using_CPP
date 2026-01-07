// 06/01/2025
// Chapter4.02.cpp
// Exercises

// [6] Write a program that converts from Celsius to Fahrenheit and from Fahrenheit to Celsius. Use estimation to see if your results are plausible

#include "PPPheaders.h"

double convertThis(double old_temp, double old_unit) {

	double res = 0;

	if (old_unit == 'c') {
		res = old_temp * 1.8 + 32;
		expect([&] {return -459.67 <= res;}, "temperature below absolute zero!");
	}
	else if (old_unit == 'f') {
		res = (old_temp - 32) / 1.8;
		expect([&] {return -273.15 <= res;}, "temperature below absolute zero!");
	}

	return res;
}

int main() {

	double inp_temp = 0, res_temp = 0;
	char inp_char;

	cout << "Please enter a temperature in either Celsius or Fahrenheit (C/F): ";
	cin >> inp_temp >> inp_char;
	inp_char = char(tolower(inp_char));

	try {
		if (!cin || (inp_char != 'c' && inp_char != 'f'))
			error("invalid input!");
		
		res_temp = convertThis(inp_temp, inp_char);
	}
	catch (exception& e) {
		cerr << '\n' << e.what() << '\n';
		return 1;
	}

	cout << "\nYour converted temperature: " << res_temp << '\n';

	return 0;
}

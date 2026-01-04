// 25/12/2025
// Chapter3.02.cpp
// Exercises

// [3] Fix the program from §3.6.3 so that it always prints out a median.
//	Median: "A number so that exactly as many elements come before it in the sequence as come after it"; "A median need not be an element of the sequence."

#include "PPPheaders.h"

int main() {

	vector<double> temps;	// temperatures
	double sum = 0, median = 0;

	cout << "Please enter temperature data: ";
	for (double temp; cin >> temp;) {	// read into temp
		temps.push_back(temp);			// put temp into vector
	}
	cout << '\n';

	if (temps.size() == 0) {
		simple_error("Invalid input!");
	}

	// compute mean temperature (average)
	for (double x : temps)
		sum += x;
	cout << "Average temperature: " << sum / temps.size() << '\n';

	// compute median temperature
	ranges::sort(temps);

	// Test for even or odd size
	if (temps.size() % 2 == 0) {

		// Takes the two middle values and calculates their average as median.
		median = (temps[temps.size() / 2] + temps[temps.size() / 2 - 1]) / 2;
		cout << "Median temperature: " << median << '\n';
	}
	else {
		median = temps[temps.size() / 2];					// 0.6 2.15 5.41 6.8 9.64 11.9 13.4 45.98
		cout << "Median temperature: " << median << '\n';
	}

	return 0;
}

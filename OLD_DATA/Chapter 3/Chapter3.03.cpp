// 25/12/2025
// Chapter3.03.cpp
// Exercises

// [4] Read a sequence of doubles into a vector. Think of each input as the distance between two cities. Output total distance, smallest and greatest distance, as well as mean (average) distance between two cities.

#include "PPPheaders.h"

int main() {

	vector<double> distances;
	double distance, sum, smallest, greatest, avg;

	sum = smallest = greatest = avg = 0;

	cout << "Enter one or more distances between two cities in km: ";
	while (cin >> distance) {
		if (distances.size() == 0) {
			smallest = greatest = distance;
		}

		distances.push_back(distance);

		sum += distance;

		if (distance < smallest) {
			smallest = distance;
		}
		else if (distance > greatest) {
			greatest = distance;
		}
	}
	if (distances.size() == 0)
		simple_error("Invalid input!");

	avg = sum / distances.size();

	cout << "\n\t\t\t*****    Results    *****\n\n";
	cout << "Total distance:\t\t" << sum << "km\tMean distance:\t\t" << avg << "km\n";
	cout << "Smallest distance:\t" << smallest << "km\t\tGreatest distance:\t" << greatest << "km\n";

	return 0;
}

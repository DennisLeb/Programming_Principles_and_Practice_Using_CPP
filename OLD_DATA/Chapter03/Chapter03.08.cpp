// 26/12/2025
// Chapter03.08.cpp
// Exercises

// [9] Write a program to calculate how many times you need to double the number 1 to reach at least 1.000, 1.000.000 and 1.000.000.000.
// [10] Try to calculate how many grains of rice were asked for. For how many squares of rice can int account for? What about double?

//		At square 32, the number becomes too large for int to store accurately. grains_of_rice shows as -2.147.483.648, this is correct except for being negative.
//		total_grains at 2147483647 is completely fine. This is because these are the smallest and largest values a normal int can hold.

//		double doesn't break. It can still store each number, but does so in exponential notation. So the number of rice grains the inventor asks for is 3.68935e+19.
//		If a chess board had 1024 squares however, double too would break. From then on it only shows "inf" as the number.

#include "PPPheaders.h"

int main() {

	vector<int> rice_tracker(3);
	double grains_of_rice = 1, total_grains = 1;

	for (int ctr = 1; ctr <= 64; ctr++) {

		cout << "Squares: " << ctr << "\t\tGrains of rice: " << grains_of_rice << "\t\tTotal Grains: " << total_grains << '\n';

		grains_of_rice *= 2;
		total_grains += grains_of_rice;

		if (total_grains >= 1000 && rice_tracker[0] == 0)
			rice_tracker[0] = ctr + 1;
		else if (total_grains >= 1000000 && rice_tracker[1] == 0)
			rice_tracker[1] = ctr + 1;
		else if (total_grains >= 1000000000 && rice_tracker[2] == 0)
			rice_tracker[2] = ctr + 1;
	}
	cout << "\nDone! You reached 1.000 grains at square " << rice_tracker[0] << ", 1.000.000 grains at square " << rice_tracker[1]
		 << " and 1.000.000.000 grains at square " << rice_tracker[2] << ".\n\n";
	cout << "In the end, you had " << total_grains << " grains of rice in total!\n";

	return 0;
}

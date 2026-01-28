// 27/01/2026
// Chapter06.03.cpp
// Exercises

//
// [11 - 1/2] Revisit two programs you wrote for the exercises in Chapter 3 and Chapter 4. Clean up that code according to the rules outlined in this chapter.
//    From Chapter 3:
//	      [9] Write a program to calculate how many times you need to double the number 1 to reach at least 1.000, 1.000.000 and 1.000.000.000.
// 
// Note: This is hilariously overkill. Nothing was improved, everything was overcomplicated and I love to see it.
//

#include "PPPheaders.h"

/**************************************************************************************************/
/*											CONSTANTS											  */
/**************************************************************************************************/

const int total_tiles = 64;
const int benchmark1 = 1000;
const int benchmark2 = 1000000;
const int benchmark3 = 1000000000;

/**************************************************************************************************/
/*										CLASS DEFINITION										  */
/**************************************************************************************************/

class rice_benchmark {
public:
	rice_benchmark() :value(0), value_not_found(true) {}
	int value;
	bool value_not_found;
};

class rice_data {
public:
	double grains_of_rice = 1;
	double total_grains = 1;
	vector<rice_benchmark> rice_tracker{ rice_benchmark(), rice_benchmark(), rice_benchmark() };		// remembers all three benchmarks
};

rice_data rd;	// provides class members

/**************************************************************************************************/
/*										CORE FUNCTION CALLS										  */
/**************************************************************************************************/

void multiplyRice() {

	for (int ctr = 1; ctr <= total_tiles; ctr++) {

		cout << "Squares: " << ctr << "\t\tGrains of rice: " << rd.grains_of_rice << "\t\tTotal Grains: " << rd.total_grains << '\n';

		rd.grains_of_rice *= 2;
		rd.total_grains += rd.grains_of_rice;

		if (rd.total_grains >= benchmark1 && rd.rice_tracker[0].value_not_found) {
			rd.rice_tracker[0].value = ctr + 1;
			rd.rice_tracker[0].value_not_found = false;
		}
		else if (rd.total_grains >= benchmark2 && rd.rice_tracker[1].value_not_found) {
			rd.rice_tracker[1].value = ctr + 1;
			rd.rice_tracker[1].value_not_found = false;
		}
		else if (rd.total_grains >= benchmark3 && rd.rice_tracker[2].value_not_found) {
			rd.rice_tracker[2].value = ctr + 1;
			rd.rice_tracker[2].value_not_found = false;
		}
	}
}

int main() {

	try {
		multiplyRice();
		cout << "\nDone! You reached 1.000 grains at square " << rd.rice_tracker[0].value << ", 1.000.000 grains at square " << rd.rice_tracker[1].value
			<< " and 1.000.000.000 grains at square " << rd.rice_tracker[2].value << ".\n\n";
		cout << "In the end, you had " << rd.total_grains << " grains of rice in total!\n";
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown error: " << endl;
		return 2;
	}
	return 0;
}

// 28/12/2025
// Chapter3.11.cpp
// Exercises

// [13] Write a program to find every prime number between 1 and 100, using the Sieve of Eratosthenes.

#include "PPPheaders.h"

vector<int> sieve(int maxPrime) {

	vector<int> primeBools(maxPrime + 1, 1);	// +1 because index starts at 0
												// Because of an issue with using vector<bool> combined with the book header file, I'll instead use ints (0 and 1)

	for (int p = 2; p * p <= maxPrime; p++) {
		if (primeBools[p])

			// Marking as false
			for (int i = p * p; i <= maxPrime; i += p)
				primeBools[i] = 0;
	}

	vector<int> primeNums;
	for (int p = 2; p <= maxPrime; p++)
		if (primeBools[p])
			primeNums.push_back(p);

	return primeNums;
}

int main() {

	int maxPrime = 100;
	vector<int> primeNums = sieve(maxPrime);
	
	for (auto x : primeNums) {
		cout << x << '\n';
	}
	
	return 0;
}

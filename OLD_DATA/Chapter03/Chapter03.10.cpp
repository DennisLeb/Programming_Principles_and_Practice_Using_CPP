// 28/12/2025
// Chapter03.10.cpp
// Exercises

// [12] Write a program to find every prime number between 1 and 100, using a vector to store them in order. Then print out your results.

#include "PPPheaders.h"

bool isPrime(int num, vector<int> primeNums) {

	if (primeNums.size() == 0) {

		// 1 can't be a prime, though it would technically fit the definition
		if (num == 1) {
			return false;
		}
		else {
			// Since num can only be 2 at this point, this check is actually useless. But it felt cheap to not include the prime logic
			// Checks if num is divisible by anything other than 1 or itself
			for (int i = 1; i <= num; i++) {
				if (num % i == 0 && i != 1 && i != num)
					return false;
			}
			return true;
		}
	}
	else {
		// Checks if num is divisible by any past prime nums, if not it's another prime
		for (int i = 0; i < primeNums.size(); i++) {
			if (num % primeNums[i] == 0)
				return false;
		}
		return true;
	}
}

int main() {

	vector<int> primeNums;

	// Finds prime nums from 1-100 
	for (int i = 1; i <= 100; i++) {
		if (isPrime(i, primeNums)) {
			primeNums.push_back(i);
		}
	}

	// Prints them out
	for (int x : primeNums) {
		cout << x << '\n';
	}

	return 0;
}

// 28/12/2025
// Chapter03.12.cpp
// Exercises

// [14] Write a program that takes an input value n and then finds the first n primes

#include "PPPheaders.h"

vector<int> sieve(int num_of_primes) {

	int range_of_primes = num_of_primes / 0.095;	// The 10.000th prime number is 104.729. Up until that maximum, prime numbers make up roughly 9.5% of numbers.

	vector<int> prime_bools(range_of_primes + 1, 1);

	for (int p = 2; p * p <= range_of_primes; p++) {
		if (prime_bools[p])

			// Marking as false
			for (int i = p * p; i <= range_of_primes; i += p)
				prime_bools[i] = 0;
	}

	vector<int> prime_nums;

	// Now fill with the requested amount of prime numbers
	for (int p = 2; prime_nums.size() < num_of_primes; p++)
		if (prime_bools[p])
			prime_nums.push_back(p);

	return prime_nums;
}


int main() {

	int num_of_primes;

	cout << "Please enter how many prime numbers you'd like as output (max. 10000): ";
	cin >> num_of_primes;

	if (num_of_primes > 10000 || num_of_primes <= 0)
		simple_error("Invalid input!");

	vector<int> prime_nums = sieve(num_of_primes);

	// Prints every requested prime number
	for (int i = 0; i < num_of_primes; i++) {
		if (i % 5 == 0) 
			cout << '\n';
		else
			cout << "\t\t";

		cout << '#' << i + 1 << ":\t" << prime_nums[i];
	}

	cout << "\n\nHere are your " << num_of_primes << " prime numbers.\n";

	return 0;
}

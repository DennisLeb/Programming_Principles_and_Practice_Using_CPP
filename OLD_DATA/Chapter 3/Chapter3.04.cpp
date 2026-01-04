// 25/12/2025
// Chapter3.04.cpp
// Exercises

// [5] Write a program to play a numbers guessing game. The user thinks of a number between 1 and 100 and the program will ask questions until it guesses correctly. It should be able to do this with no more than 7 questions.

#include "PPPheaders.h"

int main() {

	int targetNum, guessNum = 50;			// guessing begins at 50
	double maxNum = 100.0, minNum = 0.0;	// floating-point values to calculate guess more accurately
	char ans;

	cout << "Please enter a whole number from 1 to 100 and remember it well: ";
	cin >> targetNum;
	cout << '\n';

	if (targetNum < 1 || targetNum > 100)
		simple_error("Invalid input!");

	for (int i = 0; i < 7; i++) {

		if (guessNum == targetNum) {
			cout << "\nI got it! Your number is " << guessNum << "!\n";
			exit(0);
		}

		cout << "Question #" << i + 1 << ": Is the number you are thinking of less than " << guessNum << " (Y/N)? ";
		cin >> ans;

		if ((char)tolower(ans) == 'y') {
			maxNum = guessNum;
			guessNum = (int)round((minNum + maxNum) / 2);	// Get average value between minimum and maximum, then round it
		}
		else if ((char)tolower(ans) == 'n') {
			minNum = guessNum;
			guessNum = (int)round((minNum + maxNum) / 2);
		}
		else {
			cout << "\nInvalid answer, try again!\n";
			i--;
			continue;
		}
	}

	cout << "\nWhoops, looks like I couldn't guess your number...\n";

	return 0;
}

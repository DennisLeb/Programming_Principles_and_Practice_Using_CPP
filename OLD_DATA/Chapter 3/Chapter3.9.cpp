// 28/12/2025
// Chapter3.9.cpp
// Exercises

// [11] Build a "Rock, Paper, Scissors" game, where the machine takes its next answer out of a vector. For pseudo-randomness, let the user enter some value at the start.

#include "PPPheaders.h"

char getComAction(int num) {	// inspired by djb2 hash

	vector<char> comActions = { 'R', 'P', 'S' };
	unsigned long ret = 5381;
	int i = num;

	// Pseudo-random calculation. Would have used time() if not for program instructions.
	while (i != 0) {
		ret = ((ret << 5) + ret) + i;
		i /= 10;
	}

	return comActions[ret % 3];
}

int main() {

	char userAction, comAction;
	int favNum;

	cout << "***    Rock, Paper, Scissors    ***\n\n";
	cout << "Enter your next action (R/P/S): ";
	cin >> userAction;
	
	cout << "\nWhat is your favourite number? ";
	cin >> favNum;
	cout << '\n';

	switch ((char)toupper(userAction)) {
	case('R'):
		comAction = getComAction(favNum);

		if (comAction == 'R') {
			cout << "You played: Rock\tYour opponent played: Rock\n";
			cout << "It's a tie! Try again?\n";
		}
		else if (comAction == 'P') {
			cout << "You played: Rock\tYour opponent played: Paper\n";
			cout << "You lose! Better luck next time.\n";
		}
		else {
			cout << "You played: Rock\tYour opponent played: Scissors\n";
			cout << "You win! Congratulations!\n";
		}
		break;
	
	case('P'):
		comAction = getComAction(favNum);

		if (comAction == 'R') {
			cout << "You played: Paper\tYour opponent played: Rock\n";
			cout << "You win! Congratulations!\n";
		}
		else if (comAction == 'P') {
			cout << "You played: Paper\tYour opponent played: Paper\n";
			cout << "It's a tie! Try again?\n";
		}
		else {
			cout << "You played: Paper\tYour opponent played: Scissors\n";
			cout << "You lose! Better luck next time.\n";
		}
		break;

	case('S'):
		comAction = getComAction(favNum);

		if (comAction == 'R') {
			cout << "You played: Scissors\tYour opponent played: Rock\n";
			cout << "You lose! Better luck next time.\n";
		}
		else if (comAction == 'P') {
			cout << "You played: Scissors\tYour opponent played: Paper\n";
			cout << "You win! Congratulations!\n";
		}
		else {
			cout << "You played: Scissors\tYour opponent played: Scissors\n";
			cout << "It's a tie! Try again?\n";
		}
		break;

	default:
		simple_error("Invalid input!");
	}

	return 0;
}

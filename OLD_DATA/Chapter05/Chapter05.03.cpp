// 20/01/2026
// Chapter05.03.cpp
// Exercises

// [6] Redo the "Bulls and Cows" game from exercise 12 in Chapter 4 to use four letters instead of four digits.

#include "PPPheaders.h"

// This function fills the target_chars vector with random integers each time it is called
string fillTargetString(void)
{
	char new_char;
	string target_string = "";

	seed((int)time(NULL));

	// Fills target_chars with 4 different random chars
	while (target_string.length() < 4) {
		new_char = char(random_int(97, 122));

		if (!(target_string.empty())) {
			for (char x : target_string)
				if (new_char == x)
					new_char = '!';
		}

		if (new_char != '!')
			target_string += new_char;
	}

	return target_string;
}

// This function takes a string and searches it for repeating characters, returning a bool value
bool containsRepetition(string str)
{
	string altered_string = str;

	// Loops through string to find repetitions
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i != j && str[i] == str[j])
				altered_string.clear();
		}
	}

	// vector emptied if repetition found
	return altered_string.empty();
}

int main() {

	char ans = 'y';
	string user_guess;
	int cows, bulls;

	cout << "\nYou will now have to enter lowercase 4-character string guesses until you've guessed the correct string.\n\n";
	cout << "\"Bull\" means you guessed the character and the position correctly.\n";
	cout << "\"Cow\" means you only guessed the character correctly.\n";
	cout << "You have infinite guesses. Good Luck!\n\n\n";


	while (ans == 'y') {
		string target_string = fillTargetString();

			// uncomment to print out solution
		for (int i = 0; i < target_string.length(); i++)
			cout << target_string[i] << ' ';
		

		while (!target_string.empty()) {
			cout << "Enter your next guess: ";
			cin >> user_guess;

			if (cin.fail() || user_guess.length() != 4) {
				cout << "\nInvalid guess! Try again!\n\n";
				cin.clear();
				cin.ignore();
				continue;
			}

			// Detects repeating digits in guess vector
			if (containsRepetition(user_guess)) {
				cout << "\nInvalid guess, no repeating digits allowed! Try again!\n\n";
				continue;
			}

			cows = bulls = 0;

			// Gets the number of cows and bulls
			for (int i = 0; i < 4; i++) {
				// Checks if guessed number is at this position in target vector
				if (target_string[i] == user_guess[i]) {
					bulls++;
				}
				else {
					for (int j = 0; j < 4; j++) {
						// Checks if guessed number is anywhere in target vector
						if (i != j && target_string[i] == user_guess[j])
							cows++;
					}
				}
			}

			cout << "Your guess had: " << bulls << " Bull(s) and " << cows << " Cow(s).\n\n";

			if (bulls == 4) {
				cout << "Correct! You win!\n\n";
				target_string.clear();
			}
		}

		cout << "Do you want to play again? (Y/N) ";
		cin >> ans;
		cout << '\n';
		ans = char(tolower(ans));
	}
	cout << "Thanks for playing!\n";

	return 0;
}

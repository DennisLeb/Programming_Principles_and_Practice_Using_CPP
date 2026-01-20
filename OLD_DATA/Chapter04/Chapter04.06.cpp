// 07/01/2025
// Chapter04.06.cpp
// Exercises

// [12] Implement a guessing game named "Bulls and Cows". Four different random integers are selected and the user must guess them and their order based on hints from previous guesses.
// [13] Modify the program to let the user play repeatedly, using different random integers (and seeds).

#include "PPPheaders.h"

vector<int> fillTargetVec(void) 
// This function fills the target_nums vector with random integers each time it is called
{
	int new_num;
	vector<int> target_nums;

	seed((int)time(NULL));

	// Fills target_nums with 4 different random ints
	while (target_nums.size() < 4) {
		new_num = random_int(9);

		if (!(target_nums.empty())) {
			for (int x : target_nums)
				if (new_num == x)
					new_num = -1;
		}
		// Makes sure target_nums[0] is not 0
		else if (target_nums.empty() && new_num == 0)
			continue;

		if (new_num != -1)
			target_nums.push_back(new_num);
	}

	return target_nums;
}

vector<int> intToVector(int num) 
// This function takes a 4-digit int and converts it to a vector, where each element represents one digit
{
	int new_num, altered_num = num;
	vector<int> nums;

	// Fills guess_nums with user_guess to be able to compare it easier later
	for (int i = 1000; i >= 1; i /= 10) {
		// Uses integer division to get first digit
		new_num = altered_num / i;

		nums.push_back(new_num);

		// "Discards" first digit because it was already added to the vector
		altered_num -= new_num * i;
	}

	return nums;
}

bool containsRepetition(vector<int> nums) 
// This function takes an int vector and searches it for repeating elements
{
	vector<int> altered_nums = nums;

	// Loops through vector to find repetitions
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i != j && nums[i] == nums[j])
				altered_nums.clear();
		}
	}

	// vector emptied if repetition found
	return altered_nums.empty();
}

int main() {

	char ans = 'y';
	int user_guess, cows, bulls;
	vector<int> guess_nums;

	cout << "\nYou will now have to enter 4-digit numbers until you've guessed the correct number.\n\n";
	cout << "\"Bull\" means you guessed the digit and the position correctly.\n";
	cout << "\"Cow\" means you only guessed the digit correctly.\n";
	cout << "You have infinite guesses. Good Luck!\n\n\n";

	
	while (ans == 'y') {
		vector<int> target_nums = fillTargetVec();

		/*	// uncomment to print out solution for each iteration
		for (int x : target_nums)
			cout << x << ' ';
		*/

		while (!target_nums.empty()) {
			cout << "Enter your next guess: ";
			cin >> user_guess;

			if (cin.fail() || user_guess < 1000 || user_guess > 9999) {
				cout << "\nInvalid guess! Try again!\n\n";
				cin.clear();
				cin.ignore();
				continue;
			}
			// Converts guess int into vector
			guess_nums = intToVector(user_guess);

			// Detects repeating digits in guess vector
			if (containsRepetition(guess_nums)) {
				cout << "\nInvalid guess, no repeating digits allowed! Try again!\n\n";
				continue;
			}

			cows = bulls = 0;

			// Gets the number of cows and bulls
			for (int i = 0; i < 4; i++) {
				// Checks if guessed number is at this position in target vector
				if (target_nums[i] == guess_nums[i]) {
					bulls++;
				}
				else {
					for (int j = 0; j < 4; j++) {
						// Checks if guessed number is anywhere in target vector
						if (i != j && target_nums[i] == guess_nums[j])
							cows++;
					}
				}
			}

			cout << "Your guess had: " << bulls << " Bull(s) and " << cows << " Cow(s).\n\n";

			if (bulls == 4) {
				cout << "Correct! You win!\n\n";
				target_nums.clear();
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

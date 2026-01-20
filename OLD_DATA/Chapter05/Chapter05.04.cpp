// 20/01/2026
// Chapter05.04.cpp
// Exercises

// [7] Write a program that reads digits and converts them into integers. Handle numbers with one, two, three or four digits.

#include "PPPheaders.h"

// controls char input and returns as an int
int handleInput() {

	char new_char = 0;
	cin >> new_char;

	switch (new_char) {
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9': {
		cin.putback(new_char);
		int new_int;
		cin >> new_int;
		return new_int;
	}
	case ';':
		return -1;
	default:
		error("bad input");
	}
}
// converts into integer and outputs result
void handleOutput(vector<int> nums) {

	int added_num;

	switch (nums.size()) {
	case 1:
		added_num = nums[0];
		cout << added_num << " is " << nums[0] << " ones.\n";
		break;
	case 2:
		added_num = nums[0] * 10 + nums[1];
		cout << added_num << " is " << nums[0] << " tens and " << nums[1] << " ones.\n";
		break;
	case 3:
		added_num = nums[0] * 100 + nums[1] * 10 + nums[2];
		cout << added_num << " is " << nums[0] << " hundreds and " << nums[1] << " tens and " << nums[2] << " ones.\n";
		break;
	case 4:
		added_num = nums[0] * 1000 + nums[1] * 100 + nums[2] * 10 + nums[3];
		cout << added_num << " is " << nums[0] << " thousands and " << nums[1] << " hundreds and " << nums[2] << " tens and " << nums[3] << " ones.\n";
		break;
	default:
		error("bad vector size");
	}
}

int main() {

	vector<int> input_nums;
	cout << "Enter numbers with up to four-digits, each input separated by a space (';' to stop input)\n\n>> ";

	try {
		for (int i = 0; cin && i < 4; i++) {
			input_nums.push_back(handleInput());
			if (input_nums[i] == -1) {
				input_nums.pop_back();
				break;
			}
		}
		handleOutput(input_nums);
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "unknown error\n";
		return 2;
	}
	return 0;
}

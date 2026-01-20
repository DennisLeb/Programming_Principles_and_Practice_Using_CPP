// 07/01/2025
// Chapter04.07.cpp
// Exercises

// [14] Read (weekday, value) pairs from standart input. Collect all the values for each weekday in a separate vector<int>. Write out every value out from each vector and the sum from each vector. Accept weekday synonyms (Mon, monday). Write out the number of rejected values.

#include "PPPheaders.h"

int main() {

	char ans = 'y';
	int new_num, sum, rejected = 0;
	string weekday;
	vector<int> mon_nums, tue_nums, wed_nums, thu_nums, fri_nums, sat_nums, sun_nums;

	while (char(tolower(ans)) == 'y') {
		cout << "Please enter a pair of weekdays and integer values: ";
		cin >> weekday >> new_num;
		cout << '\n';

		// Converts weekday to lowercase letters
		for (int i = 0; i < weekday.length(); i++)
			weekday[i] = char(tolower(weekday[i]));

		if (weekday == "monday" || weekday == "mon")
			mon_nums.push_back(new_num);
		else if (weekday == "tuesday" || weekday == "tue")
			tue_nums.push_back(new_num);
		else if (weekday == "wednesday" || weekday == "wed")
			wed_nums.push_back(new_num);
		else if (weekday == "thursday" || weekday == "thu")
			thu_nums.push_back(new_num);
		else if (weekday == "friday" || weekday == "fri")
			fri_nums.push_back(new_num);
		else if (weekday == "saturday" || weekday == "sat")
			sat_nums.push_back(new_num);
		else if (weekday == "sunday" || weekday == "sun")
			sun_nums.push_back(new_num);
		else {
			cerr << "weekday rejected!\n\n";
			rejected++;
		}

		cout << "Do you want to enter another pair? (Y/N) ";
		cin >> ans;
		cout << '\n';
	}
	cout << "\nLet's look at the results...\n\n";

	if (mon_nums.empty())
		cout << "No data entries for Monday!\n\n";
	else {
		cout << "Monday: ";
		sum = 0;
		for (int x : mon_nums) {
			cout << x << ' ';
			sum += x;
		}
		cout << "\nThat's " << sum << " in total!\n\n";
	}

	if (tue_nums.empty())
		cout << "No data entries for Tuesday!\n\n";
	else {
		cout << "Tuesday:\n";
		sum = 0;
		for (int x : tue_nums) {
			cout << x << ' ';
			sum += x;
		}
		cout << "\nThat's " << sum << " in total!\n\n";
	}

	if (wed_nums.empty())
		cout << "No data entries for Wednesday!\n\n";
	else {
		cout << "Wednesday:\n";
		sum = 0;
		for (int x : wed_nums) {
			cout << x << ' ';
			sum += x;
		}
		cout << "\nThat's " << sum << " in total!\n\n";
	}

	if (thu_nums.empty())
		cout << "No data entries for Thursday!\n\n";
	else {
		cout << "Thursday:\n";
		sum = 0;
		for (int x : thu_nums) {
			cout << x << ' ';
			sum += x;
		}
		cout << "\nThat's " << sum << " in total!\n\n";
	}

	if (fri_nums.empty())
		cout << "No data entries for Friday!\n\n";
	else {
		cout << "Friday:\n";
		sum = 0;
		for (int x : fri_nums) {
			cout << x << ' ';
			sum += x;
		}
		cout << "\nThat's " << sum << " in total!\n\n";
	}

	if (sat_nums.empty())
		cout << "No data entries for Saturday!\n\n";
	else {
		cout << "Saturday:\n";
		sum = 0;
		for (int x : sat_nums) {
			cout << x << ' ';
			sum += x;
		}
		cout << "\nThat's " << sum << " in total!\n\n";
	}

	if (sun_nums.empty())
		cout << "No data entries for Sunday!\n\n";
	else {
		cout << "Sunday:\n";
		sum = 0;
		for (int x : sun_nums) {
			cout << x << ' ';
			sum += x;
		}
		cout << "\nThat's " << sum << " in total!\n\n";
	}
	cout << "A total of " << rejected << " values were rejected!\n";

	return 0;
}

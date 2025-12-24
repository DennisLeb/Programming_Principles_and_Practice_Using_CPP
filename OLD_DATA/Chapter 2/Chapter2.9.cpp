// Date 22/12/2025
// File Chapter2.8.cpp
// Exercises

// [11] Write a program that prompts the user about every coin type they have, then output each of those as well as their total sum.

#include "PPPheaders.h"

int sumUpMoney() {

	//	0.01	  0.05		 0.10	  0.25		  0.50			 1.00
	int pennyAmt, nickelAmt, dimeAmt, quarterAmt, halfDollarAmt, dollarCoinAmt;
	double total = 0.0;

	cout << "Please enter in whole numbers...\n";

	cout << "\nHow many pennies do you have? ";
	cin >> pennyAmt;
	if (pennyAmt < 0)
		simple_error("You can't have a negative amount of pennies!");

	cout << "\nHow many nickels do you have? ";
	cin >> nickelAmt;
	if (nickelAmt < 0)
		simple_error("You can't have a negative amount of nickels!");

	cout << "\nHow many dimes do you have? ";
	cin >> dimeAmt;
	if (dimeAmt < 0)
		simple_error("You can't have a negative amount of dimes!");

	cout << "\nHow many quarters do you have? ";
	cin >> quarterAmt;
	if (quarterAmt < 0)
		simple_error("You can't have a negative amount of quarters!");

	cout << "\nHow many half dollar coins do you have? ";
	cin >> halfDollarAmt;
	if (halfDollarAmt < 0)
		simple_error("You can't have a negative amount of half dollar coins!");

	cout << "\nHow many one dollar coins do you have? ";
	cin >> dollarCoinAmt;
	if (dollarCoinAmt < 0)
		simple_error("You can't have a negative amount of one dollar coins!");

	cout << '\n';

	if (pennyAmt == 1) {
		total += .01;
		cout << "You have one penny! That's 0.01$!\n";
	}
	else {
		// safe type conversion, because double > int (8 byte > 4 byte)
		total += pennyAmt * .01;
		cout << "You have " << pennyAmt << " pennies! That's " << pennyAmt * .01 << "$!\n";
	}

	if (nickelAmt == 1) {
		total += .05;
		cout << "You have one nickel! That's 0.05$!\n";
	}
	else {
		total += nickelAmt * .05;
		cout << "You have " << nickelAmt << " nickels! That's " << nickelAmt * .05 << "$!\n";
	}

	if (dimeAmt == 1) {
		total += .1;
		cout << "You have one dime! That's 0.10$!\n";
	}
	else {
		total += dimeAmt * .1;
		cout << "You have " << dimeAmt << " dimes! That's " << dimeAmt * .1 << "$!\n";
	}

	if (quarterAmt == 1) {
		total += .25;
		cout << "You have one quarter! That's 0.25$!\n";
	}
	else {
		total += quarterAmt * .25;
		cout << "You have " << quarterAmt << " quarters! That's " << quarterAmt * .25 << "$!\n";
	}
	
	if (halfDollarAmt == 1) {
		total += .5;
		cout << "You have one half dollar coin! That's 0.50$!\n";
	}
	else {
		total += halfDollarAmt * 0.5;
		cout << "You have " << halfDollarAmt << " half dollar coins! That's " << halfDollarAmt * 0.5 << "$!\n";
	}
	
	if (dollarCoinAmt == 1) {
		total += 1.0;
		cout << "You have one one dollar coin! That's 1$!\n";
	}
	else {
		total += dollarCoinAmt * 1.0;
		cout << "You have " << dollarCoinAmt << " one dollar coins! That's " << dollarCoinAmt * 1.0 << "$!\n";
	}
	cout << "\nIn total you have " << total << "$!\n";

	return 0;
}

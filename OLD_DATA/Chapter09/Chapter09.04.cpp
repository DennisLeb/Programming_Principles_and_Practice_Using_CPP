// 19/02/2026
// Chapter09.04.cpp
// Exercises

//
// [4] Write a program that prompts the user to enter several integers in any combination of octal, decimal, or hexadecimal,
//     using the 0 (for octal) and 0x (for hexadecimal) base prefixes; interprets the numbers correctly;
//     and converts them to decimal form.
//     Then your program should output the values in properly spaced columns like this:
//         0x43		hexadecimal		converts to		67		decimal
//         0123		octal			converts to		83		decimal
//         65		decimal			converts to		65		decimal
//
//     Note:
//         I did not enjoy this one.
//

#include "PPPheaders.h"

struct Number
{
	enum class Base
	{
		dec, oct, hex
	};
	
	Number() :num{ 0 }, base{Base::dec} {}
	
	int num;
	Base base;
};

istream& operator>>(istream& is, Number& num) 
{
	char first = '\0', second = '\0';

	is >> first;
	// Did input succeed?
	if (!is)
		return is;
	
	// Is it CTRL+Z?
	if (first == (char)26)	// 26 == CTRL+Z
	{
		is.clear(ios::eofbit);	// I don't really understand why it doesn't set the istream state to eof() on its own if it detects CTRL+Z, but this works.
		return is;
	}

	// Is it a non-zero decimal?
	if (first != '0')
	{
		is.unget();
		num.base = Number::Base::dec;
		return is >> dec >> num.num;
	}

	is >> second;
	// Did input succeed?
	if (!is)
	{
		// Is it a decimal 0?
		if (is.eof())
		{
			num.num = 0;
			is.clear();
			return is;
		}
		else
			return is;
	}

	// Is it a hexadecimal?
	if (second == 'x')
	{
		num.base = Number::Base::hex;
		return is >> hex >> num.num;
	}
	// Is it an octal?
	else if (isdigit(second))
	{
		is.unget();
		num.base = Number::Base::oct;
		return is >> oct >> num.num;
	}
	else
	{
		is.clear(ios::failbit);
		return is;
	}
}

int main()
{
	try
	{
		vector<Number> nums;
		Number new_num;

		cout << "Enter some numbers (terminate with CTRL+Z) > ";
		while (cin >> new_num && !cin.eof())		// Why is the second condition even necessary???
			nums.push_back(new_num);

		if (!cin && !cin.eof() || nums.empty())		// Accept eof as failstate unless vector is empty
			error("invalid input");

		cout << "\nNumber\t\tBase\t\t\t\t\tConverted Number\tConverted Base" << endl;
		cout << "-----------------------------------------------------------------------------------------------" << endl;

		for (const Number& num : nums)
		{
			switch (num.base)
			{
			case Number::Base::dec:
				cout << dec << num.num << "\t\t" << "decimal" << "\t\t" << "converts to" << "\t\t" << num.num << "\t\t\t" << "decimal" << endl;
				break;

			case Number::Base::oct:
				cout << oct << '0' << num.num << "\t\t" << "octal" << "\t\t" << "converts to" << "\t\t" << dec << num.num << "\t\t\t" << "decimal" << endl;
				break;
			
			case Number::Base::hex:
				cout << hex << "0x" << num.num << "\t\t" << "hexadecimal" << '\t' << "converts to" << "\t\t" << dec << num.num << "\t\t\t" << "decimal" << endl;
				break;

			default:
				error("invalid base");
			}
		}

		return 0;
	}
	catch (exception& e)
	{
		cerr << "error: " << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "unknown error" << endl;
		return 2;
	}
}

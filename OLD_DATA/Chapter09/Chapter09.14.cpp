// 24/02/2026
// Chapter09.14.cpp
// Exercises

//
// [16] Write a program that produces the sum of all the numbers in a file of whitespace-separated integers.
//

#include "PPPheaders.h"

int main()
{
	try
	{
		ifstream ifs{ "Chapter09.14.1.txt" };
		if (!ifs)
			error("unable to open input file");

		int sum = 0;
		for (auto [temp, ch] = tuple{ 0, '\0' }; (ch = ifs.get()) != EOF;)	// Structured binding and tuple to have multiple loop variables (still clueless)
		{
			if (isspace(ch))
				continue;
			if ((!isdigit(ch) && ch != '-') || !ifs)
				error("invalid input file format");

			ifs.unget();
			ifs >> temp;
			sum += temp;
		}
		ifs.close();

		cout << "The sum of all the numbers in that file is: " << sum << endl;

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

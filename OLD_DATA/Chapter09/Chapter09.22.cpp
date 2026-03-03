// 03/03/2026
// Chapter09.22.cpp
// Exercises

//
// [26] Write a program that produces the sum of all the whitespace-separated integers in a text file.
//		For example, "bears: 17 elephants 9 end" should output 26.
//

#include "PPPheaders.h"

const string file_name{ "Chapter09.22.1.txt" };

int main()
{
	try
	{
		ifstream ifs{ file_name };
		if (!ifs)
			error("unable to open input file");
		
		int sum = 0;
		for (auto [ch, val] = tuple<char, int>{ '\0', 0 }; (ch = ifs.get()) != EOF;)
		{
			if (!isdigit(ch))
				continue;

			ifs.unget();
			ifs >> val;
			sum += val;
		}
		cout << "The sum of every integer in that file is: " << sum << '.' << endl;

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

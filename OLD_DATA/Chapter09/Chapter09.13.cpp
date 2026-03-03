// 24/02/2026
// Chapter09.13.cpp
// Exercises

//
// [15] Write a program to read a file of whitespace-separated numbers and output them in order (low -> high), one value per line.
//		Write a value only once, and if it occurs more than once write the count of its occurences on its line.
//		For example, 7 5 5 7 3 117 5 should give:
//			3
//			5 3
//			7 2
//			117
//

#include "PPPheaders.h"

// This is the first recursive function I ever wrote myself. Somehow this worked on the first try. Holy heck
int getCount(const int& num, const int& pos, const vector<int>& vec)
{
	if (pos + 1 != vec.size() && vec[pos + 1] == num)
		return (getCount(num, pos + 1, vec) + 1);
	return 1;
}

int main()
{
	try
	{
		ifstream ifs{ "Chapter09.13.1.txt" };
		if (!ifs)
			error("unable to open input file");

		vector<int> vec;
		for (auto [temp, ch] = tuple{ 0, '\0' }; (ch = ifs.get()) != EOF;)	// Experimenting with structured bindings and tuples to have multiple loop variables (I have no clue how this actually works)
		{
			if (isspace(ch))
				continue;
			if ((!isdigit(ch) && ch != '-') || !ifs)
				error("invalid input file format");

			ifs.unget();
			ifs >> temp;
			vec.push_back(temp);
		}
		ifs.close();

		ranges::sort(vec);

		for (int i = 0; i < vec.size(); ++i)
		{
			int count = getCount(vec[i], i, vec);
			if (count > 1)
			{
				cout << vec[i] << ' ' << count << endl;
				i += count - 1;		// Compensate for skipping ahead
			}
			else
				cout << vec[i] << endl;
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

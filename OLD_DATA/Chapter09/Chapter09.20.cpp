// 02/03/2026
// Chapter09.20.cpp
// Exercises

//
// [24] Write a program that takes two files containing sorted whitespace-separated words and merges them, preserving order.
//

#include "PPPheaders.h"

const string file_name_1{ "Chapter09.20.1.txt" };
const string file_name_2{ "Chapter09.20.2.txt" };
const string file_name_3{ "Chapter09.20.3.txt" };

int main()
{
	try
	{
		ifstream ifs_1{ file_name_1 };
		if (!ifs_1)
			error("unable to open first input file");

		ifstream ifs_2{ file_name_2 };
		if (!ifs_2)
			error("unable to open second input file");

		ofstream ofs{ file_name_3 };
		if (!ofs)
			error("unable to open output file");

		vector<string> strings;
		for (auto [new_str, ch] = tuple<string, char>{ "", '\0' }; (ch = ifs_1.get()) != EOF;)
		{
			if (isspace(ch) || ifs_1.eof())
			{
				strings.push_back(new_str);
				new_str.clear();
				continue;
			}
			new_str += ch;
		}
		ifs_1.close();
		
		for (auto [new_str, ch] = tuple<string, char>{ "", '\0' }; (ch = ifs_2.get()) != EOF;)
		{
			if (isspace(ch) || ifs_2.eof())
			{
				strings.push_back(new_str);
				new_str.clear();
				continue;
			}
			new_str += ch;
		}
		ifs_2.close();
		
		ranges::sort(strings);
		for (string& str : strings)
		{
			ofs << str;
			if (str != *(--strings.end()) /* Is this the last element? */)
				ofs << ' ';
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

// 23/02/2026
// Chapter09.08.cpp
// Exercises

//
// [9] Write a function vector<string> split(const string& s) that returns a vector of whitespace-separated substrings from the argument s.
//
// [10] Write a function vector<string> split(const string& s, const string& w) that returns a vector of whitespace-separated substrings from the argument s,
//      where whitespace is defined as "ordinary whitespace" plus the characters in w.
//

#include "PPPheaders.h"

bool findCharInString(const char& target_ch, const string& comp_str)
{
	for (const char& comp_ch : comp_str)
		if (target_ch == comp_ch)
			return true;
	return false;
}

vector<string> split(const string& s, const string& w)
{
	stringstream ss{ s };
	string str;
	vector<string> split_strings;

	for (char ch; (ch = ss.get()) != EOF;)
	{
		switch (ch)
		{
		case ' ': case '\t': case '\n':
			if (!str.empty())
			{
				split_strings.push_back(str);
				str.clear();
			}
			break;

		default:
			if (findCharInString(ch, w))
			{
				if (!str.empty())
				{
					split_strings.push_back(str);
					str.clear();
				}
				break;
			}
			str += ch;
			break;
		}
	}
	split_strings.push_back(str);
	return split_strings;
}

int main()
{
	try
	{
		string test_str{ "Hello World, this is a test. I needed more words to test this program, which is why I wrote some more." };
		vector<string> split_strings = split(test_str, "test");

		for (string& str : split_strings)
			cout << str << ' ';
		cout << endl;

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

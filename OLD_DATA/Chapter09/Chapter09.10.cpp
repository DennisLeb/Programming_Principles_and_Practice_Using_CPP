// 24/02/2026
// Chapter09.10.cpp
// Exercises

//
// [12] Reverse the order of words (defined as whitespace-separated strings) in a file.
//		For example, Norwegiean Blue parrot becomes parrot Blue Norwegian.
//		Assume that all the strings from the file will fit into memory at once.
//

#include "PPPheaders.h"

vector<string> split(const string& s)
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
		ifstream ifs{ "Chapter09.10.1.txt" };
		if (!ifs)
			error("unable to open input file");

		string temp_str;

		for (char ch = '\0'; (ch = ifs.get()) != EOF;)
			temp_str += ch;
		ifs.close();

		vector<string> split_strings = split(temp_str);
		reverse(split_strings.begin(), split_strings.end());

		ofstream ofs{ "Chapter09.10.1.txt" };
		if (!ofs)
			error("unable to open output file");

		for (const string& str : split_strings)
			ofs << str << ' ';
		cout << "Done!" << endl;

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

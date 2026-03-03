// 24/02/2026
// Chapter09.09.cpp
// Exercises

//
// [11] Reverse the order of characters in a text file. For example, asdfghjkl becomes lkjhgfdsa.
//		Warning: There is no really good, portable, and efficient way of reading a file backward.
//

#include "PPPheaders.h"

int main()
{
	try
	{
		ifstream ifs{ "Chapter09.09.1.txt" };
		if (!ifs)
			error("unable to open input file");
		string temp_str;

		ifs >> temp_str;
		/*
		for (char ch = '\0'; (ch = ifs.get()) != EOF;)
			temp_str += ch;
		*/

		ifs.close();
		reverse(temp_str.begin(), temp_str.end());

		ofstream ofs{ "Chapter09.09.1.txt" };
		if (!ofs)
			error("unable to open output file");

		ofs << temp_str;
		ofs.close();

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

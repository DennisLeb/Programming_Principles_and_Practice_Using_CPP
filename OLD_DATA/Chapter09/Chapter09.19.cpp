// 02/03/2026
// Chapter09.19.cpp
// Exercises

//
// [23] Write a program that accepts two file names and produces a new file that is the contents of the first, followed by the contents of the second;
//		that is, the program concatenates the two files.
//

#include "PPPheaders.h"

const string file_name_1{ "Chapter09.19.1.txt" };
const string file_name_2{ "Chapter09.19.2.txt" };
const string file_name_3{ "Chapter09.19.3.txt" };

int main()
{
	try
	{
		/* The exercise wants you to do this, but it isn't very practical for testing.
		string my_file_name_1;
		string my_file_name_2;

		cout << "Enter the first file name > ";
		cin >> my_file_name_1;
		if (!cin)
			error("invalid input");

		cout << "Enter the second file name > ";
		cin >> my_file_name_2;
		if (!cin)
			error("invalid input");
		*/

		ifstream ifs_1{ file_name_1 };
		if (!ifs_1)
			error("unable to open first input file");

		ifstream ifs_2{ file_name_2 };
		if (!ifs_2)
			error("unable to open second input file");
		
		ofstream ofs{ file_name_3 };
		if (!ofs)
			error("unable to open output file");
		
		for (string str; getline(ifs_1, str);)
		{
			ofs << str;
			if (!ifs_1.eof())
				ofs << endl;
		}
		ifs_1.close();

		for (string str; getline(ifs_2, str);)
		{
			ofs << str;
			if (!ifs_2.eof())
				ofs << endl;
		}
		ifs_2.close();
		ofs.close();

		/* This solution is worse, I think
		string str;

		for (char ch = '\0'; (ch = ifs_1.get()) != EOF;)
			str += ch;
		ifs_1.close();

		for (char ch = '\0'; (ch = ifs_2.get()) != EOF;)
			str += ch;
		ifs_2.close();

		ofs << str;
		ofs.close();
		*/

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

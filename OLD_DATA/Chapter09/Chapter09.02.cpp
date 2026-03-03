// 19/02/2026
// Chapter09.02.cpp
// Exercises

//
// [2] Write a program that given a file name and a word will output each line that contains that word together with the line number.
//

#include "PPPheaders.h"

int main()
{
	try
	{
		string ifname, target_str;
		cout << "Enter the name of the file you'd like to open > ";	// enter "Chapter09.02.1.txt"
		cin >> ifname;
		if (!cin)
			error("invalid input");

		ifstream ifs{ ifname };
		if (!ifs)
			error("unable to open file");

		cout << "\nEnter the word you want to look for > ";
		cin >> target_str;
		if (!cin)
			error("invalid input");

		cout << endl;
		string str;
		for (int i = 1; getline(ifs, str); i++)
		{
			// str.find() finds an argument substring within a string. If it doesn't find the substring, it returns string::npos.
			if (str.find(target_str) != string::npos)
				cout << target_str << " found in line " << i << ": " << str << endl;
		}

		ifs.close();

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

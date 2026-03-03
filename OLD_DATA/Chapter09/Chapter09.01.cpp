// 19/02/2026
// Chapter09.01.cpp
// Exercises

//
// [1] Write a program that reads a text file and converts its input to all lowercase, producing a new file.
//

#include "PPPheaders.h"

int main()
{
	try
	{
		ifstream ifs{ "Chapter09.01.1.txt" };
		if (!ifs)
			error("unable to open input file");

		ofstream ofs{ "Chapter09.01.2.txt" };
		if (!ofs)
			error("unable to open output file");

		string str;
		while (getline(ifs, str))
		{
			for (char ch : str)
				ofs << (char)tolower(ch);
			ofs << endl;
		}

		ifs.close();
		ofs.close();

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

// 24/02/2026
// Chapter09.12.cpp
// Exercises

//
// [14] Write a program that reads a file of whitespace separated numbers and
//		outputs a file of numbers using scientific format and precision 8 in four fields of 20 characters per line.
//
// Note:
//     I'm not sure what four fields of 20 characters per line is supposed to mean,
//     so I made it output a table with four rows per column and each entry has 20 characters.
//

#include "PPPheaders.h"

int main()
{
	try
	{
		ifstream ifs{ "Chapter09.12.1.txt" };
		if (!ifs)
			error("unable to open input file");
		
		ofstream ofs{ "Chapter09.12.2.txt" };
		if (!ofs)
			error("unable to open output file");

		char ch = '\0';
		double temp_db = 0.0;
		for (int i = 1; (ch = ifs.get()) != EOF; ++i)
		{
			if (isspace(ch))
			{
				--i;
				continue;
			}
			if ((!isdigit(ch) && ch != '.' && ch != '-') || !ifs)
				error("invalid input file format");

			ifs.unget();
			ifs >> setprecision(8) >> scientific >> temp_db;

			ofs << setw(20) << setprecision(8) << scientific << temp_db;
			if (i % 4 == 0)
				ofs << endl;
		}
		ifs.close();
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

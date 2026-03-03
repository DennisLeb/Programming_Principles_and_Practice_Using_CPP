// 24/02/2026
// Chapter09.11.cpp
// Exercises

//
// [13] Write a program that reads a text file and writes out how many characters of each character classification are in the file.
//

#include "PPPheaders.h"

int main()
{
	try
	{
		ifstream ifs{ "Chapter09.11.1.txt" };
		if (!ifs)
			error("unable to open input file");

		int alphas, digits, alnums, xdigits, uppers, lowers, cntrls, puncts, prints, graphs;
		alphas = digits = alnums = xdigits = uppers = lowers = cntrls = puncts = prints = graphs = 0;

		for (char ch = '\0'; (ch = ifs.get()) != EOF;)
		{
			if (isalpha(ch))
				alphas++;
			if (isdigit(ch))
				digits++;
			if (isalnum(ch))
				alnums++;
			if (isxdigit(ch))
				xdigits++;
			if (isupper(ch))
				uppers++;
			if (islower(ch))
				lowers++;
			if (iscntrl(ch))
				cntrls++;
			if (ispunct(ch))
				puncts++;
			if (isprint(ch))
				prints++;
			if (isgraph(ch))
				graphs++;
		}
		ifs.close();

		cout << "This file holds:\n" << endl;
		cout << alphas << " letters;" << endl;
		cout << digits << " decimal digits;" << endl;
		cout << alnums << " letters or decimal digits;" << endl;
		cout << xdigits << " hexadecimal digits;" << endl;
		cout << uppers << " uppercase letters;" << endl;
		cout << lowers << " lowercase letters;" << endl;
		cout << cntrls << " control characters;" << endl;
		cout << puncts << " special symbols;" << endl;
		cout << prints << " printable characters;" << endl;
		cout << graphs << " letters, decimal digits, or special symbols." << endl;

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

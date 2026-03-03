// 20/02/2026
// Chapter09.05.cpp
// Exercises

//
// [5] Write a program that reads strings and for each string outputs the character classification of each character:
//         - isalpha(c)  -> Is c a letter?
//         - isdigit(c)  -> Is c a decimal digit?
//         - isalnum(c)  -> Is c a letter or decimal digit?
//         - isxdigit(c) -> Is c a hexadecimal digit ('a'..'f' or 'A'..'F')?
//         - isupper(c)  -> Is c an uppercase letter?
//         - islower(c)  -> Is c a lowercase letter?
//         - iscntrl(c)  -> Is c a control character (ASCII 0..31 or 127)?
//         - ispunct(c)  -> Is c not a letter, digit, whitespace, or invisible control character (special symbols)?
//         - isprint(c)  -> Is c printable?
//         - isgraph(c)  -> Is c a letter, a decimal digit, or ispunct(c)?
//
//     Note that a character can have several classifications.
//

#include "PPPheaders.h"

int main()
{
	try
	{
		vector<string> strings;

		cout << "Enter some strings (terminate by typing \"quit\") > ";
		for (string new_str; cin >> new_str && new_str != "quit";)
			strings.push_back(new_str);
		
		if (!cin && !cin.eof() || strings.empty())		// Accept eof as failstate unless vector is empty
			error("invalid input");

		for (int i = 0; i < strings.size(); i++)
		{
			cout << "String #" << i+1 << ": \"" << strings[i] << '\"' << endl;
			for (char& ch : strings[i])		// Very ugly but works.
			{
				if (isalpha(ch))
					cout << "\t\'" << ch << '\'' << " is a letter." << endl;
				if (isdigit(ch))
					cout << "\t\'" << ch << '\'' << " is a decimal digit." << endl;
				if (isalnum(ch))
					cout << "\t\'" << ch << '\'' << " is a letter or a decimal digit." << endl;
				if (isxdigit(ch))
					cout << "\t\'" << ch << '\'' << " is a hexadecimal digit." << endl;
				if (isupper(ch))
					cout << "\t\'" << ch << '\'' << " is an uppercase letter." << endl;
				if (islower(ch))
					cout << "\t\'" << ch << '\'' << " is a lowercase letter." << endl;
				if (iscntrl(ch))
					cout << "\t\'" << ch << '\'' << " is a control character." << endl;
				if (ispunct(ch))
					cout << "\t\'" << ch << '\'' << " is a special symbol." << endl;
				if (isprint(ch))
					cout << "\t\'" << ch << '\'' << " is printable." << endl;
				if (isgraph(ch))
					cout << "\t\'" << ch << '\'' << " is a letter, a decimal digit, or a special symbol." << endl;
				cout << endl;
			}
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

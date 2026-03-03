// 20/02/2026
// Chapter09.06.cpp
// Exercises

//
// [6] Write a program that replaces punctuation with whitespace.
//     Consider '.' (dot), ';' (semicolon), ',' (comma), '?' (question mark), '-' (dash), ''' (single-quote) punctuation characters.
//     Don't modify characters within a pair of double quotes '"'.
//
// [7] Modify the program from the previous exercise so that it replaces don't with do not, can't with cannot, etc.;
//     leaves hyphens within words intact (e.g. as-if, wanna-be, etc.);
//     and converts all characters to lower case
//

#include "PPPheaders.h"

char modifyChar(const char& ch)
{
	switch (ch)
	{
	case '.': case ';': case ',':
	case '?': case '\'': case '-':
		return ' ';

	default:
		return (char)tolower(ch);
	}
}

void replaceString(string& str)
{
	// Seems very overkill, but I wanted to experiment
	struct String_pair
	{
		String_pair(string str_1, string str_2) :original_str{ str_1 }, replacement_str{ str_2 } {}

		string original_str;
		string replacement_str;
	};
	const vector<String_pair> vec{ { "don t", "do not" }, { "can t", "cannot" }, { "won t", "will not" } };	// all single quotes have been replaced with whitespace
	int index = -1;

	// Find substring (original string)
	for (int i = 0; i < vec.size(); i++)
		if (str.find(vec[i].original_str, str.length() - 5) != string::npos)	// Begin search at length() - 5 (-1 is obvious; -4 because this is the maximum length of a substring)
		{
			index = i;
			break;
		}
	if (index == -1)	// Didn't find substring
		return;

	str.replace(str.length() - 5, str.length() - 1, vec[index].replacement_str);
	return;
}

string loopThroughInput()
{
	string str;
	int opening_quotes_found = -1; // -1 for false position
	for (char ch; cin >> noskipws >> ch;)	// noskipws -> reads whitespace too
	{
		switch (ch)
		{
		case (char)26:
			goto escape_loop;

		case '"':
			str += ch;
			if (opening_quotes_found == -1)
				opening_quotes_found = (int)str.length() - 1; // Remember that position

			else
				opening_quotes_found = -1;	// Discard that position
			break;

		case '-':
			if (isalpha(str[str.length() - 1]) && isalpha(cin.peek()))
			{
				str += ch;
				break;
			}
			[[fallthrough]];

		default:
			if (opening_quotes_found == -1)
			{
					
				str += modifyChar(ch);
				if (str.back() == 't')
					replaceString(str);
			}
			else
				str += ch;	// Do not modify if opening_quotes_found
			break;
		}
	}
	escape_loop:

	// If quotes have not been closed by the end, go back to saved pos and modify from there on
	if (opening_quotes_found != -1)
		for (int i = opening_quotes_found; i < str.length(); i++)
		{
			if (str[i] == '-' && isalpha(str[i - 1]) && (i + 1 < str.length() ? isalpha(str[i + 1]) : false))
				continue;
			str[i] = modifyChar(str[i]);
			if (str[i] == 't')
				replaceString(str);
		}

	return str;
}

int main()
{
	try
	{
		cout << "Enter some text (terminate with CTRL+Z) > ";
		string str = loopThroughInput();

		if (cin.fail() || cin.bad() || str.empty())
			error("invalid input");

		cout << "\nOutput:\n\n" << str << endl;

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

// Test values:
//     thi's -i.s a t,es,t "don't m.odif,,y in he're" bu.t "d,o mo-dify thi's
//     tHIs won't spell "won't." But This Will speLL cannot: can't
//     "as-if as-if" "as-if as-if
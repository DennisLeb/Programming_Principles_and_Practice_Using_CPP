// 23/02/2026
// Chapter09.07.cpp
// Exercises

//
// [8] Use the program from the previous exercise to make a sorted list of words.
//     Run the result on a multi-page text file, look at the result and see if you can improve the program to make a better list.
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
	const vector<String_pair> vec{	// all single quotes have already been replaced with whitespace
		{ "don t", "do not" },
		{ "isn t", "is not" },
		{ "can t", "cannot" },
		{ "won t", "will not" },
		{ "wasn t", "was not" }
	};
	int index = -1;

	// Find substring (original string)
	for (int i = 0; i < vec.size(); i++)
		if (str.find(vec[i].original_str, str.length() - 6) != string::npos)	// Begin search at length() - 6 (-1 is obvious; -5 because this is the maximum length of a substring)
		{
			index = i;
			break;
		}
	if (index == -1)	// Didn't find substring
		return;

	str.replace(str.length() - vec[index].original_str.length(), str.length() - 1, vec[index].replacement_str);
	return;
}

string loopThroughInput(ifstream& ifs)
{
	string str;
	int opening_quotes_found = -1; // -1 for false position
	for (char ch; ifs >> noskipws >> ch;)	// noskipws -> reads whitespace too
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
			if (isalpha(str[str.length() - 1]) && isalpha(ifs.peek()))
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
		ifstream ifs{ "Chapter09.07.1.txt" };
		if (!ifs)
			error("could not open input file");

		ofstream ofs{ "Chapter09.07.2.txt" };
		if (!ofs)
			error("could not open output file");

		string str = loopThroughInput(ifs);
		
		if (!ifs && !ifs.eof() || str.empty())
			error("invalid input");

		stringstream ss{ str };

		vector<string> sorted_strings;
		for (string new_string; getline(ss, new_string, ' ');)
			sorted_strings.push_back(new_string);

		ranges::sort(sorted_strings);
		
		for (string& str: sorted_strings)
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

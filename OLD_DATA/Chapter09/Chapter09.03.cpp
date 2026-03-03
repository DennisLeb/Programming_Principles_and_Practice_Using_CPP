// 19/02/2026
// Chapter09.03.cpp
// Exercises

//
// [3] Write a program that removes all vowels from a file. For example, "Once upon a time!" becomes "nc pn  tm!".
//
// Note:
//     If this wasn't just a simple exercise, you really shouldn't use a name like temp.txt for the output file.
//     What if the user already has a file by that name for some reason? It'd be overwritten along with all its data.
//     
//     One solution is to change the name temp.txt to something like format("{}{}.txt", getDate(), getTime()).
//     
//     Alternatively you could cut out the temp file alltogether by doing something like this:
//         1. Open input file
//         2. Read every line
//         3. Store altered strings in a vector
//         4. Close input file
//         5. Open same file as output file
//         6. Overwrite with vector elements.
//         7. Close output file
// 
//     This would be somewhat more elegant, but I wanted to mess around with remove() and rename().
//

#include "PPPheaders.h"

int main()
{
	try
	{
		ifstream ifs{ "Chapter09.03.1.txt" };
		if (!ifs)
			error("unable to open input file");
		
		ofstream ofs{ "temp.txt" };
		if (!ofs)
			error("unable to open output file");

		string str;
		while (getline(ifs, str))
		{
			string new_str;
			for (char ch : str)
			{
				switch ((char)tolower(ch))
				{
				case 'a': case 'e':
				case 'i': case 'o': case 'u':	// I don't consider 'y' to be a vowel here
					break;

				default:
					new_str += ch;
					break;
				}
			}
			ofs << new_str << endl;
		}

		ifs.close();
		ofs.close();

		// Both return 0 if successful
		if (remove("Chapter09.03.1.txt"))	// Delete original file (remember to close it before running this program)
		{
			if (remove("temp.txt"))	// Clean-up (if this fails too, delete temp.txt manually)
				error("unable to delete original file and temp file");

			error("unable to delete original file");
		}

		if (rename("temp.txt", "Chapter09.03.1.txt"))	// Rename modified file to simulate an overwrite
			error("unable to rename file");

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


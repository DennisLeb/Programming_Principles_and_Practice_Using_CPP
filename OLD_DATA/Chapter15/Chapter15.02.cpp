// 28/05/2026
// Chapter15.02.cpp
// Exercises

//
// [6] Write a program that reads characters from 'cin' into an array that you allocate on the free store.
//     Read individual characters until an exclamation mark (!) is entered.
//     Do not use a std::string. Do not worry about memory exhaustion.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <exception>

int main()
{
	try
	{
		std::vector<char> char_vec;

		// Input
		for (char ch = '\0'; static_cast<int>(ch = std::cin.get()) != EOF && ch != '!';)
			char_vec.push_back(ch);

		// Alloc
		size_t size = char_vec.size();
		char *p_ch = new char[size + 1]; // Make room for the null terminator

		// Output
		for (size_t i = 0; i < char_vec.size(); ++i)  
		{
			p_ch[i] = char_vec[i];
			std::cout << p_ch[i];
		}

		p_ch[size] = '\0';

		// Dealloc
		delete[] p_ch;

		return 0;
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unknown error: " << std::endl;
		return 2;
	}
}
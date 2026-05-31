// 29/05/2026
// Chapter16.01.cpp
// Exercises

//
// [1] Write a function, 'void to_lower(char *s)', that replaces all uppercase characters in the C-style string 's' with their lowercase equivalents.
//     For example "Hello, World!" becomes "hello, world!".
//     Do not use any standard-library function.
//     A C-style string is a zero-terminated array of characters, so if you find a 'char' with the value '0' or '\0' you are at the end.
//

#include <cstdio>
#include <malloc.h>
#include <string.h>


void to_lower(char *s)	// Uses no std function
{
	for (size_t i = 0; s[i] != '\0'; ++i)
		if ((int)s[i] > 64 && (int)s[i] < 91) // Is s[i] A-Z?
			s[i] = char((int)s[i] + 32);
}

int main()
{
	int valid = 0;
	
	constexpr int buffer = 256; // leave room for 255 chars as well as a null-terminator
	char *str = (char*)malloc(buffer * sizeof(char));

	while ((valid = scanf_s("%s", str, buffer)) != EOF)
	{
		if (strcmp(str, "QUIT"))
			break;

		if (valid)
		{
			to_lower(str);
			printf("%s\n", str);
		}
		else
			while (getchar() != '\n') {} // Flush input buffer
		
		printf("String size: %llu\n", sizeof(str));
	}

	free(str);
}

// 31/05/2026
// Chapter16.02.cpp
// Exercises

//
// [4] Write a function, 'int str_cmp(const char *s1, const char *s2)', that compares C-style strings.
//     Let it return a negative number if 's1' is lexicographically before 's2', zero is 's1' equals 's2',
//     and a positive number if 's1' is lexicographically after 's2'.
//     Do not use any standard library functions.
//     Do not use any subscripting; use the dereference operator ('*') instead.
//

#include <cstdio>


int str_cmp(const char *s1, const char *s2)
{
	for (size_t i = 0; *(s1 + i) != '\0' && *(s2 + i) != '\0'; ++i)
	{
		if (*(s1 + i) == *(s2 + i))
			continue;
		else
			return (int)*(s1 + i) - (int)*(s2 + i);
	}
	return 0;
}

int main()
{
	const char *str1 = "String0", *str2 = "String1";

	printf("%d", str_cmp(str1, str2));
}

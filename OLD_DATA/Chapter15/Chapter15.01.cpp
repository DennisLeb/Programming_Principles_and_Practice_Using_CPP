// 28/05/2026
// Chapter15.01.cpp
// Exercises

//
// [4] Consider the memory layout in  §15.4. 
//     Write a program that tells the order in which static storage, the stack, and the free store are laid out in memory.
//     In which direction does the stack grow: upward toward higher addresses or downward toward lower addresses?
//     In an array on the free store, are elements with higher indices allocated at higher or lower addresses?
//
//     Ans:
//         The stack variable 'address' seems to shift downward in address location. 
//         Each new memory address of 'address' is the previous location subtracted by exactly 304 (when converted to decimal).
// 
//         The dynamically allocated array moves upwards to toward higher addresses, incrementing its address by sizeof(type).
//         I.e. an 'int' array address adds 4 per element, a 'double' array address adds 8 per element and so on.
//

#include<iostream>

using namespace std;

int g1 = 0;
int g2 = 0;
int g3 = 0;

int recursion(int i)
{
	int address = 0;
	cout << &address << endl;

	if (i < 3)
		return recursion(++i);
	else
		return i;
}

int main()
{
	cout << "Stack addresses: " << endl;
	int placeholder = recursion(0);


	int *pi = new int[5];

	cout << "\nFree store/heap addresses: " << endl;
	for (int i = 0; i < 5; ++i)
		cout << &pi[i] << endl;
	
	delete[] pi;


	cout << "\nStatic storage addresses: " << endl;
	cout << &g1 << endl;
	cout << &g2 << endl;
	cout << &g3 << endl;


	return 0;
}

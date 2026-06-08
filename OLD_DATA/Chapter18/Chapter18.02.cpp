// 08/06/2026
// Chapter18.02.cpp
// Exercises

//
// [3] Write a template class 'Pair' that can hold a pair of values of any type.
//     Use this to implement a simple symbol table like the one we used in the calculator (§6.8).
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;


template<class T, class U>
class Pair
{
public:
	Pair() = delete;	// Default constructor
	Pair(const T &a_t, const U &a_u) :m_first(a_t), m_second(a_u) {}	// Argument constructor
	Pair(const Pair &) = default;	// Copy constructor
	Pair(Pair &&) = default;	// Move constructor

	~Pair() = default;	// Destructor

	Pair &operator=(const Pair &) = default;	// Copy assignment
	Pair &operator=(Pair &&) = default;	// Move assignment

	const T &first() const { return m_first; }
	const U &second() const { return m_second; }

private:
	T m_first;
	U m_second;
};

int main()
{
	vector<Pair<string, int>> symbol_table{ { "first", 1 }, { "second", 2 }, { "third", 3 } };

	for (const Pair<string, int> &p : symbol_table)
		cout << '(' << p.first() << ", " << p.second() << ')' << endl;
}

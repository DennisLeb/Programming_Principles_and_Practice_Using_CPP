// 08/06/2026
// Chapter18.01.cpp
// Exercises

//
// [1] Write a template function 'add()' that adds the elements of one 'vector<T>' to the elements of another;
//     for example, 'add(v1, v2)' should do 'v1[i] += v2[i]' for each element of 'v1'.
//
// [2] Write a template function that takes a 'vector<T> vt' and a 'vector<U> vu' as arguments and returns the sum of all 'vt[i] * vu[i]'s.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;


template<class T>
void add(vector<T> &v1, vector<T> &v2)
{
	const size_t smaller = v1.size() <= v2.size() ? v1.size() : v2.size();
	for (size_t i = 0; i < smaller; ++i)
		v1[i] += v2[i];
}

void test_add()
{
	vector<int> vi1{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> vi2{ -14, 6, 7, 23, 8, 28, 6, 7, 23, 8, 101 };

	vector<string> vs1{ "hello", "world", "lol" };
	vector<string> vs2{ "pied", "piper" };

	add(vi1, vi2);

	cout << "vi1:" << endl;
	for (const auto &i : vi1)
		cout << i << ' ';

	cout << "\nvi2:" << endl;
	for (const auto &i : vi2)
		cout << i << ' ';
	cout << endl;

	add(vs1, vs2);

	cout << "vs1:" << endl;
	for (const auto &i : vs1)
		cout << i << ' ';

	cout << "\nvs2:" << endl;
	for (const auto &i : vs2)
		cout << i << ' ';
	cout << endl;
}


template<class T, class U>
T product_sum(const vector<T> &vt, const vector<U> &vu)
{
	T sum = 0;
	const size_t smaller = vt.size() <= vu.size() ? vt.size() : vu.size();
	for (size_t i = 0; i < smaller; ++i)
		sum += vt[i] * vu[i];
	return sum;
}

void test_product_sum()
{
	const vector<int> vi{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	const vector<double> vd{ 9.14, 1.124, 32.1, -70.098, 13.76, -2.2356, 6.521, 9.215, 82.4, 62.1 };

	cout << "sum == " << product_sum(vd, vi) << endl;
}


int main()
{
	//test_add();
	test_product_sum();
}

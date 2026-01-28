// 28/01/2026
// Chapter06.04.cpp
// Exercises

//
// [11 - 2/2] Revisit two programs you wrote for the exercises in Chapter 3 and Chapter 4. Clean up that code according to the rules outlined in this chapter.
//    From Chapter 4:
//        [11] Write a program that writes out the first n values of the Fibonacci series.
//
// Note: Gotta have at least a little fun, no?
//

#include "PPPheaders.h"

/**************************************************************************************************/
/*										CLASS DEFINITION										  */
/**************************************************************************************************/

class fib_nums {
public:
	vector<int> fib_vec;
	int buffer = 0;
	void get() {

		fib_vec.push_back(buffer);
	}
};

fib_nums fib;

/**************************************************************************************************/
/*										CORE FUNCTION CALLS										  */
/**************************************************************************************************/

int getInput() {

	int n_amt;
	cout << "Please enter how many Fibonacci numbers you'd like written out: ";
	cin >> n_amt;
	cout << endl;

	for (int i = 0; cin.fail() || n_amt <= 0; i++) {
		switch (i) {
		case 0:
			cout << "Whoops! That wasn't quite right" << endl << "Just try again > ";
			break;
		case 1:
			cout << "Not quite my tempo, huh? Hahaha! Just a little banter to keep things light." << endl << "Here, try again > ";
			break;
		case 2:
			cout << "That's uhh.. come on you've got it this time." << endl << "Try again > ";
			break;
		case 3: case 4:
			cout << "..and again > ";
			break;
		case 5:
			cout << "..... > ";
			break;
		case 6:
			cout << "Maybe I wasn't being specific enough? It's um.. you're supposed to enter a number > ";
			break;
		case 7:
			cout << "A positive number.... you got all that? > ";
			break;
		case 8:
			cout << "Because like.. the program can't really print a negative amount. > ";
			break;
		case 9:
			cout << "Or none. Zero is neutral, right? Not positive. You learn that in school? > ";
			break;
		case 10:
			cout << "Also if you're trying decimal numbers... don't? > ";
			break;
		case 11:
			cout << "It also can't print 1.5 lines, can it? No I don't think so. > ";
			break;
		case 12:
			cout << "Or.. no it be able to. Because the .5 just gets cut off, no? > ";
			break;
		case 13:
			cout << "Yeah, yeah. Try that, try 1.5 > ";
			break;
		case 14:
			cout << "Right.. I think I'm done. I'll just leave it to the clanker... > ";
			break;
		default:
			cout << "AUTOMATIC INPUT CONTROL; PLEASE ENTER __VAR_NAME__; >> ";
		}
		cin >> n_amt;
		cout << endl;
	}

	return n_amt;
}

void findFibNums(int n) {

	for (int i = 0; i < n; i++) {
		// Calculates next fib_num from the last two
		if (i > 1) {
			// Checks whether int would overflow
			if (fib.fib_vec[i - 1] > INT_MAX - fib.fib_vec[i - 2])
				error("fib_nums: int overflow");

			fib.buffer = fib.fib_vec[i - 2] + fib.fib_vec[i - 1];
		}
		// else if there are no last two
		else
			fib.buffer = 1;

		fib.get();
	}
	return;
}

int main() {

	try {
		int n_amt = getInput();

		findFibNums(n_amt);

		for (auto x : fib.fib_vec) {
			cout << x << endl;
		}
		return 0;
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown error" << endl;
		return 2;
	}
}

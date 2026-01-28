// 18/01/2026
// Chapter05.01.cpp
// Exercises

// [2] Add the ability to use {} as well as () in the program, so that {(4 + 5) * 6} / (3 + 4) will be a valid expression.
//
// [3] Add a factorial operator: use a suffix ! operator to represent it. The expression 7! means 7*6*5*4*3*2*1. Make it bind tighter than * or /.
//		0! equals 1 by standart mathematical definition. For x! assign x to an int, since factorial is only defined for non-negative whole numbers.

#include "PPPheaders.h"

class Token {

public:
	char kind;										// what kind of Token
	double value;									// for numbers: a value
	Token(char k) :kind{k}, value{0.0}{}			// construct from one value
	Token(char k, double v) :kind{k}, value{v}{}	// construct from two values
};
class Token_stream {

public:
	Token_stream() :full{false}, buffer{0}{}
	Token get();									// get a Token
	void putback(Token t);							// put a Token back

private:
	bool full = false;								// is there a Token in the buffer?
	Token buffer;									// putback() saves its Token here
};

Token Token_stream::get() {

	if (full) {										// do we already have a Token ready? (was putback() called?)
		full = false;								// remove Token from buffer
		return buffer;
	}
	char ch = 0;
	if (!(cin >> ch))									// note that >> skips whitespace
		error("no input");

	switch (ch) {
	case ';':
	case 'q':
	case '(': case ')': case '{': case '}':
	case '+': case '-': case '*': case '/': case '!':
		return Token(ch);							// let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9': {
		cin.putback(ch);							// put digit back into the input stream
		double val = 0;
		cin >> val;									// read a floating-point number
		return Token('8', val);						// let '8' represent "a number"
	}
	default:
		error("bad Token");
	}
}
void Token_stream::putback(Token t) {
	
	if (full)
		error("putback() into a full buffer");
	buffer = t;										// copy t to buffer
	full = true;									// buffer is now full
}

Token_stream ts;									// provides get() and putback()
double expression();								// declaration so that primary() can call expression()
double factorial();									// declaration so that primary() can call factorial()

// deal with numbers, parentheses and curly brackets
double primary() {

	Token t = ts.get();
	switch (t.kind) {
	case '(': {
		double d = expression();
		t = ts.get();
		if (t.kind != ')')
			error("\')\' expected");
		return d;
	}
	case '{': {
		double d = expression();
		t = ts.get();
		if (t.kind != '}')
			error("\'}\' expected");
		return d;
	}
	case '!': {
		double d = factorial();
		return d;
	}
	case '8':										// we use '8' to represent a number
		return t.value;								// return the number's value

	default:
		error("primary expected");
	}
}
// deal with factorials
double factorial() {

	int left = int(primary());
	if (left < 0)
		error("negative factorial");
	if (left == 0)
		return 1;

	for (int i = left - 1; i > 0; i--)
		left *= i;
	return left;
}
// deal with '*' and '/'
double term() {

	double left = primary();
	Token t = ts.get();								// get the next Token from the Token stream
	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;

		case '/': {
			double d = primary();
			if (d == 0)
				error("divide by 0");
			left /= d;
			t = ts.get();
			break;
		}

		default:
			ts.putback(t);							// put t back into the Token stream
			return left;
		}
	}
}
// deal with '+' and '-'
double expression() {
	
	double left = term();							// read and evaluate a Term
	Token t = ts.get();								// get the next Token from the Token stream
	while (true) {
		switch (t.kind) {
		case '+':
			left += term();							// evaluate Term and add
			t = ts.get();
			break;

		case '-':
			left -= term();
			t = ts.get();
			break;

		default:
			ts.putback(t);							// put t back into the Token stream
			return left;							// finally: no more '+' or '-'; return the answer
		}
	}
}

// main loop and deal with errors
int main() {

	double val = 0;

	try {
		while (cin) {
			cout << "> ";
			Token t = ts.get();
			if (t.kind == 'q')
				return 0;
			if (t.kind == ';') {
				cout << "= " << val << '\n';
				continue;
			}
			else
				ts.putback(t);
			
			val = expression();
		}
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		return 2;
	}
}

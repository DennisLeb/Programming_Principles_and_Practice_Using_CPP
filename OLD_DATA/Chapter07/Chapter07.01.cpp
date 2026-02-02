// 30/01/2026
// Chapter07.01.cpp
// Exercises

//
// [1] Modify the calculator from Chapter 6 to make the input stream (Token_stream) an explicit parameter, instead of a global variable.
//     Also give the Token_stream constructor an istream& parameter.
//

/*	Simple Calculator
*
*	This program implements a basic expression calculator.
*	Input from cin; output to cout. Before evaluation input is converted into Tokens.
*	Besides traditional operators, there are in-built functions available and the user may also define their own variables and constants during run-time.
*
*	The grammar for input is:
*
*
*	Calculation:
*		Statement
*		Calculation Statement
*	Statement:
*		Declaration
*		Expression
*		Expression Print Expression
*		Print
*		Quit
*	Print:
*		';'
*	Quit:
*		"exit"
*	Declaration:
*		"let" Name '=' Expression
*		"let" "const" Name '=' Expression
*		Name '=' Expression
*	Expression:
*		Term
*		Expression '+' Term
*		Expression '-' Term
*	Term:
*		Primary
*		Term '*' Primary
*		Term '/' Primary
*		Term '%' Primary
*	Primary:
*		Number
*		'(' Expression ')'
*		'-' Primary
*		'+' Primary
*		"sqrt" '(' Expression ')'
*		"pow" '(' Expression ',' Primary ')'
*	Number:
*		floating-point-literal
*
*/

#include "PPPheaders.h"

/**************************************************************************************************/
/*											CONSTANTS											  */
/**************************************************************************************************/

const char number = '8';
const char print = ';';
const char name = 'N';
const char assign = '=';

const string prompt = "> ";
const string result = "= ";

const char let = 'L';
const string declkey = "let";

const char constant = 'C';
const string constkey = "const";

const char sqroot = 'S';
const string sqrtkey = "sqrt";

const char pow_of = 'P';
const string powkey = "pow";

const char quit = 'Q';
const string quitkey = "quit";

const char help = 'H';
const string helpkey = "help";

/**************************************************************************************************/
/*										CLASS DEFINITIONS										  */
/**************************************************************************************************/

// Token used to organize input
class Token {
public:
	Token(char ch) :kind(ch), value(0) {}					// three separate constructor functions
	Token(char ch, double val) :kind(ch), value(val) {}
	Token(char ch, string n) :kind(ch), name(n) {}
	char kind;					// what kind of Token
	double value = 0.0;			// numeric Token 
	string name;				// name Token for variables
};

// used to input and output Tokens as needed
class Token_stream {
public:
	Token_stream() :full(0), buffer(0), final_input(1), inp_stream(cin) {}
	Token get();				// converts one char into a Token
	void putback(Token t);		// puts Token into buffer
	void ignore(char);			// error recovery
	bool final_input;			// tells program when to output new prompt
	istream& inp_stream;

private:
	bool full;
	Token buffer;
};

// get a Token from the stream
Token Token_stream::get() {

	if (full) {			// checks buffer first
		full = false;
		return buffer;
	}

	char ch = 0;
	do {
		cin >> noskipws >> ch;			// the noskipws flag lets cin read whitespace (spaces, tabs and newlines)
	} while (ch == ' ' || ch == '\t');	// flushes spaces and tabs

	switch (ch) {
	case '(': case ')':		// is it an operator?
	case '+': case '-':
	case '*': case '/':
	case '%':
	case '=':
	case ',':
		return Token{ ch };

	case print:				// is it a ';'?
		cin >> ch;
		if (ch == '\n')		// is it the last expression before newline input?
			final_input = true;
		else
			final_input = false;

		cin.putback(ch);
		return Token{ print };

	case '.':				// is it a number?
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9': {
		cin.putback(ch);			// puts number char into cin buffer
		double val;
		cin >> val;					// gets entire number, not just one char
		return Token{ number, val };
	}

	case '\n':				// is it a newline?
		final_input = true;
		return Token{ print };

	default:
		if (isalpha(ch)) {			// is it a variable name or the variable declaration key or [..]?
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
				s += ch;

			cin.putback(ch);
			if (s == declkey)
				return Token{ let };

			if (s == constkey)
				return Token{ constant };

			if (s == sqrtkey)
				return Token{ sqroot };

			if (s == powkey)
				return Token{ pow_of };

			if (s == quitkey)
				return Token{ quit };

			if (s == helpkey)
				return Token{ help };

			return Token{ name, s };
		}
		error("Bad token - Token_stream::get()");
		return 0;		// This will never return, I just needed the compiler to shut up
	}
}

// place a Token in the stream
void Token_stream::putback(Token t) {

	if (full)	// should be impossible
		error("putback() into full buffer - Token_stream::putback()");

	buffer = t;
	full = true;
}

// discards input up to and including c
void Token_stream::ignore(char c) {

	if (full && c == buffer.kind) { // is c inside buffer?
		full = false;
		return;
	}
	full = false;

	char ch = 0;
	while (cin >> ch)
		if (ch == c)
			return;
}

// for run-time variable definition
class Variable {
public:
	Variable(string n, double v, bool b) :name(n), value(v), is_const(b) {}
	string name;
	double value;
	bool is_const;
};

// for managing variables
class Symbol_table {
public:
	double get(string s);
	void set(string s, double d);
	bool isDeclared(string s);
	double declare(string var, double val, bool is_const);

private:
	vector<Variable> var_table;
};

// read value of a defined variable
double Symbol_table::get(string s) {

	for (int i = 0; i < var_table.size(); ++i)	// searches vector until s is found
		if (var_table[i].name == s)
			return var_table[i].value;

	error(s, " is an undefined name - Symbol_table::get()");
	return 0;		// This will never return, I just needed the compiler to shut up
}

// change value of a defined variable
void Symbol_table::set(string s, double d) {

	for (int i = 0; i <= var_table.size(); ++i)
		if (var_table[i].name == s) {
			if (var_table[i].is_const)
				error(s, " is a constant variable - Symbol_table::set()");

			var_table[i].value = d;
			return;
		}
	error(s, " is an undefined name - Symbol_table::set()");
}

// has the variable been declared/defined?
bool Symbol_table::isDeclared(string s) {

	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s)
			return true;

	return false;
}

// defines a new variable
double Symbol_table::declare(string var, double val, bool is_const) {

	if (isDeclared(var))
		error(var, " declared twice - Symbol_table::declare()");

	var_table.push_back(Variable{ var, val, is_const });
	return val;
}

/**************************************************************************************************/
/*											CALCULATION											  */
/**************************************************************************************************/

Symbol_table st;		// provides var_table and several functions to operate on it

double expression(Token_stream&);	// lets primary() call expression()
double primary(Token_stream&);		// lets getPow() and getSqrt() call primary()

// handles syntax for standard library sqrt() implementation — sqrt(x)
double getSqrt(Token_stream& ts) {

	Token t = ts.get();
	if (t.kind != '(') {
		ts.putback(t);
		error("'(' expected - getSqrt()");
	}

	ts.putback(t);			// put '(' back to have primary() return the in-parentheses expression
	double d = primary(ts);
	if (d < 0)
		error("negative square root - getSqrt()");

	return sqrt(d);
}

// handles syntax for standard library pow() implementation — pow(x, i)
double getPow(Token_stream& ts) {

	Token t = ts.get();
	if (t.kind != '(') {
		ts.putback(t);
		error("'(' expected - getPow()");
	}
	double x = expression(ts);		// for pow(x, i), x should be an expression  

	t = ts.get();
	if (t.kind != ',') {
		ts.putback(t);
		error("',' expected - getPow()");
	}

	int i = narrow<int>(primary(ts));
	if (i == 0)
		return 1;

	t = ts.get();
	if (t.kind != ')') {
		ts.putback(t);
		error("')' expected - getPow()");
	}

	return pow(x, i);
}

// handles primarys
double primary(Token_stream& ts) {

	Token t = ts.get();
	switch (t.kind) {
	case number:
		return t.value;

	case '(': {
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')') {
			ts.putback(t);
			error("')' expected - primary()");
		}
		return d;
	}

	case '-':					// unary minus prefix
		return -primary(ts);

	case '+':					// unary plus prefix
		return primary(ts);

	case sqroot:
		return getSqrt(ts);

	case pow_of:
		return getPow(ts);

	case name: {
		string t_name = t.name;		// store the name to check next input
		t = ts.get();
		if (t.kind == assign) {
			double d = expression(ts);
			st.set(t_name, d);	// assign new value to t_name variable
		}
		else
			ts.putback(t);			// if t.kind != '='

		return st.get(t_name);
	}

	default:
		error("primary expected - primary()");
		return 0;		// This will never return, I just needed the compiler to shut up
	}
}

// handles terms (*, /)
double term(Token_stream& ts) {

	double left = primary(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {

		case '*':
			left *= primary(ts);
			break;

		case '/': {
			double d = primary(ts);
			if (d == 0) error("divide by zero - term()");
			left /= d;
			break;
		}

		case '%': {
			int i1 = narrow<int>(left);
			int i2 = narrow<int>(primary(ts));
			if (i2 == 0)
				error("% divide by zero - term()");
			left = i1 % i2;
			break;
		}

		default:
			ts.putback(t);
			return left;
		}
	}
}

// handles expressions (+, -)
double expression(Token_stream& ts) {

	double left = term(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term(ts);
			break;

		case '-':
			left -= term(ts);
			break;

		default:
			ts.putback(t);
			return left;
		}
	}
}

/**************************************************************************************************/
/*											USER VARIABLES										  */
/**************************************************************************************************/

// controls variable definition syntax
double declaration(Token_stream& ts) {

	bool is_const = false;		// false by default
	Token t = ts.get();
	if (t.kind == constant) {
		is_const = true;
		t = ts.get();
	}

	if (t.kind != name)
		error("name expected in declaration - declaration()");

	string name = t.name;
	if (st.isDeclared(name))
		error(name, " declared twice - declaration()");

	Token t2 = ts.get();
	if (t2.kind != '=')
		error("'=' expected - declaration()");

	double d = expression(ts);
	st.declare(name, d, is_const);
	return d;
}

/**************************************************************************************************/
/*										CORE FUNCTION CALLS										  */
/**************************************************************************************************/

// checks for declaration keyword (let)
double statement(Token_stream& ts) {

	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration(ts);

	default:
		ts.putback(t);
		return expression(ts);
	}
}

// calculation loop and error handling (with recovery)
void calculate() {

	// provides get(), putback() and ignore()
	Token_stream ts;

	cout << "Type \"help\" for instructions.\n" << endl;
	while (true)
		try {
			if (ts.final_input)		// only output prompt if all previous results were output
				cout << prompt;

			Token t = ts.get();
			while (t.kind == print)		// first discard all "prints"
				t = ts.get();

			if (t.kind == help) {
				cout << "\t\t***    How to use   ***\n" << endl;
				cout << "Enter any expressions using the following operators:  +, -, *, /" << endl;
				cout << "Enter any integer expressions using the following operator:  %\n" << endl;
				cout << "There are also the functions pow() and sqrt():" << endl;
				cout << "pow(x, i) - with i being any integer" << endl;
				cout << "sqrt(x) - with x being any non-negative number\n" << endl;
				cout << "Additionally you may define your own variables using the following syntax: \"let\" NAME \"=\" EXPRESSION" << endl;
				cout << "For defining constants, you may add the const keyword after the let keyword.\n" << endl;
				cout << "The following constants have been pre-defined: pi = 3.1415926535, e = 2.7182818284\n" << endl;
				cout << "Hit Enter to confirm your input. For multiple expressions in one line, separate them with ';'.\n" << endl;
				cout << "Type \"quit\" to quit the program.\n" << endl;
				continue;
			}

			if (t.kind == quit)
				return;

			ts.putback(t);
			cout << result << statement(ts) << endl;
		}
	catch (exception& e) {
		cerr << "error: " << e.what() << endl;
		ts.ignore(print);
	}
	catch (...) {
		cerr << "unknown error" << endl;
		ts.ignore(print);
	}
}

// handles fatal errors
int main() {

	try {
		// predefine names
		st.declare("pi", 3.1415926535, true);
		st.declare("e", 2.7182818284, true);

		calculate();
		return 0;
	}
	catch (exception& e) {
		cerr << "fatal error: " << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown fatal error\n";
		return 2;
	}
}

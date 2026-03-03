// 02/03/2026
// Chapter09.18.cpp
// Exercises

//
// [22] Make a version of the calculator from Chapter 6 that accepts Roman numerals rather than the usual Arabic ones,
//		for example, XXI + CIV == CXXV
//

#include "Chapter09.18.h"	// PPPheaders.h is already included in this

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
class Token 
{
public:
	Token(char ch) :kind(ch) {}					// three separate constructor functions
	Token(char ch, Roman::Roman_int val) :kind(ch), value(val) {}
	Token(char ch, string n) :kind(ch), name(n) {}
	char kind;					// what kind of Token
	Roman::Roman_int value;		// numeric Token 
	string name;				// name Token for variables
};

// used to input and output Tokens as needed
class Token_stream 
{
public:
	Token_stream() :full(0), buffer(0), final_input(1) {}
	Token get();				// converts one char into a Token
	void putback(Token t);		// puts Token into buffer
	void ignore(char);			// error recovery
	bool final_input;			// 

private:
	bool full;
	Token buffer;
};

// get a Token from the stream
Token Token_stream::get() 
{
	if (full)	// checks buffer first
	{			
		full = false;
		return buffer;
	}

	char ch = '\0';
	do 
	{
		cin >> noskipws >> ch;			// the noskipws flag lets cin read whitespace (spaces, tabs and newlines)
	} while (ch == ' ' || ch == '\t');	// flushes spaces and tabs

	switch (ch) 
	{
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

	case '0': case '1':	case '2': case '3':	case '4':	// is it a number or a Roman character?
	case '5': case '6':	case '7': case '8':	case '9':
	case 'I': case 'V': case 'X': case 'L':
	case 'C': case 'D': case 'M':
	{
		cin.putback(ch);
		Roman::Roman_int val;
		cin >> val;
		return Token{ number, val };
	}

	case '\n':				// is it a newline?
		final_input = true;
		return Token{ print };

	default:
		if (isalpha(ch))	// is it a variable name or the variable declaration key or [..]?
		{			
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
		return NULL;		// This will never return, I just needed the compiler to shut up
	}
}

// place a Token in the stream
void Token_stream::putback(Token t)
{
	if (full)	// should be impossible
		error("putback() into full buffer - Token_stream::putback()");

	buffer = t;
	full = true;
}

// discards input up to and including c
void Token_stream::ignore(char c) 
{
	if (full && c == buffer.kind)	// is c inside buffer?
	{ 
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
class Variable 
{
public:
	Variable(string n, Roman::Roman_int v, bool b) :name(n), value(v), is_const(b) {}
	string name;
	Roman::Roman_int value;
	bool is_const;
};

// for managing variables
class Symbol_table 
{
public:
	Roman::Roman_int get(string s);
	void set(string s, Roman::Roman_int d);
	bool isDeclared(string s);
	Roman::Roman_int declare(string var, Roman::Roman_int val, bool is_const);

private:
	vector<Variable> var_table;
};

// read value of a defined variable
Roman::Roman_int Symbol_table::get(string s)
{
	for (int i = 0; i < var_table.size(); ++i)	// searches vector until s is found
		if (var_table[i].name == s)
			return var_table[i].value;

	error(s, " is an undefined name - Symbol_table::get()");
	return NULL;		// This will never return, I just needed the compiler to shut up
}

// change value of a defined variable
void Symbol_table::set(string s, Roman::Roman_int d)
{
	for (int i = 0; i <= var_table.size(); ++i)
		if (var_table[i].name == s) 
		{
			if (var_table[i].is_const)
				error(s, " is a constant variable - Symbol_table::set()");

			var_table[i].value = d;
			return;
		}
	error(s, " is an undefined name - Symbol_table::set()");
}

// has the variable been declared/defined?
bool Symbol_table::isDeclared(string s) 
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s)
			return true;

	return false;
}

// defines a new variable
Roman::Roman_int Symbol_table::declare(string var, Roman::Roman_int val, bool is_const)
{
	if (isDeclared(var))
		error(var, " declared twice - Symbol_table::declare()");

	var_table.push_back(Variable{ var, val, is_const });
	return val;
}

/**************************************************************************************************/
/*											CALCULATION											  */
/**************************************************************************************************/

Token_stream ts;		// provides get(), putback() and ignore()
Symbol_table st;		// provides var_table and several functions to operate on it

Roman::Roman_int expression();	// lets primary() call expression()
Roman::Roman_int primary();		// lets getPow() and getSqrt() call primary()

// handles syntax for standard library sqrt() implementation — sqrt(x)
Roman::Roman_int getSqrt()
{
	Token t = ts.get();
	if (t.kind != '(') 
	{
		ts.putback(t);
		error("'(' expected - getSqrt()");
	}

	ts.putback(t);			// put '(' back to have primary() return the in-parentheses expression
	Roman::Roman_int d = primary();
	if (d.as_int() < 0)
		error("negative square root - getSqrt()");

	return Roman::Roman_int{ narrow<unsigned int>(sqrt(d.as_int())) };
}

// handles syntax for standard library pow() implementation — pow(x, i)
Roman::Roman_int getPow() {

	Token t = ts.get();
	if (t.kind != '(') 
	{
		ts.putback(t);
		error("'(' expected - getPow()");
	}
	Roman::Roman_int x = expression();		// for pow(x, i), x should be an expression  

	t = ts.get();
	if (t.kind != ',') 
	{
		ts.putback(t);
		error("',' expected - getPow()");
	}

	Roman::Roman_int i = primary();
	if (i.as_int() == 0)
		return 1;

	t = ts.get();
	if (t.kind != ')') 
	{
		ts.putback(t);
		error("')' expected - getPow()");
	}

	return Roman::Roman_int{ narrow<unsigned int>(pow(x.as_int(), i.as_int()))};
}

// handles primarys
Roman::Roman_int primary()
{
	Token t = ts.get();
	switch (t.kind) 
	{
	case number:
		return t.value;

	case '(': 
	{
		Roman::Roman_int d = expression();
		t = ts.get();
		if (t.kind != ')') 
		{
			ts.putback(t);
			error("')' expected - primary()");
		}
		return d;
	}

	case '+':					// unary plus prefix
		return primary();

	case sqroot:
		return getSqrt();

	case pow_of:
		return getPow();

	case name: 
	{
		string t_name = t.name;		// store the name to check next input
		t = ts.get();
		if (t.kind == assign) 
		{
			Roman::Roman_int d = expression();
			st.set(t_name, d.as_int());	// assign new value to t_name variable
		}
		else
			ts.putback(t);			// if t.kind != '='

		return st.get(t_name);
	}

	default:
		error("primary expected - primary()");
		return NULL;		// This will never return, I just needed the compiler to shut up
	}
}

// handles terms (*, /)
Roman::Roman_int term()
{
	Roman::Roman_int left = primary();
	while (true) 
	{
		Token t = ts.get();
		switch (t.kind) 
		{
		case '*':
			left *= primary().as_int();		// !!!!!!!!
			break;

		case '/': 
		{
			Roman::Roman_int d = primary();
			if (d.as_int() == 0) error("divide by zero - term()");
			left /= d.as_int();
			break;
		}

		case '%': 
		{
			Roman::Roman_int i1 = left;
			Roman::Roman_int i2 = primary();
			if (i2.as_int() == 0)
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
Roman::Roman_int expression()
{
	Roman::Roman_int left = term();
	while (true) 
	{
		Token t = ts.get();
		switch (t.kind) 
		{
		case '+':
			left += term().as_int();
			break;

		case '-':
			left -= term().as_int();
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
Roman::Roman_int declaration()
{
	bool is_const = false;		// false by default
	Token t = ts.get();
	if (t.kind == constant)
	{
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

	Roman::Roman_int d = expression();
	st.declare(name, d, is_const);
	return d;
}

/**************************************************************************************************/
/*										CORE FUNCTION CALLS										  */
/**************************************************************************************************/

// checks for declaration keyword (let)
Roman::Roman_int statement()
{
	Token t = ts.get();
	switch (t.kind) 
	{
	case let:
		return declaration();

	default:
		ts.putback(t);
		return expression();
	}
}

// calculation loop and error handling (with recovery)
void calculate() 
{
	cout << "Type \"help\" for instructions.\n" << endl;
	while (true) 
	{
		try 
		{
			if (ts.final_input)		// only output prompt if all previous results were output
				cout << prompt;

			Token t = ts.get();
			while (t.kind == print)		// first discard all "prints"
				t = ts.get();

			if (t.kind == help) 
			{
				cout << "\t\t***    How to use   ***\n" << endl;
				cout << "Enter any integer expressions using the following operators:  +, -, *, /, %\n" << endl;
				cout << "End each expression with a ';'. Hit Enter to confirm your input.\n" << endl;
				cout << "There are also the functions pow() and sqrt(), also accepting integers only:" << endl;
				cout << "pow(x, i)" << endl;
				cout << "sqrt(x) - with x being any non-negative integer\n" << endl;
				cout << "Additionally you may define your own variables using the following syntax: \"let\" NAME \"=\" EXPRESSION" << endl;
				cout << "For defining constants, you may add the const keyword after the let keyword.\n" << endl;
				cout << "Type \"quit\" to quit the program.\n" << endl;
				cout << "If you ever get stuck, try entering a ';'.\n" << endl;
				continue;
			}

			if (t.kind == quit)
				return;

			ts.putback(t);
			cout << result << statement() << endl;
		}
		catch (exception& e) 
		{
			cerr << "error: " << e.what() << endl;
			ts.ignore(print);
		}
		catch (...) 
		{
			cerr << "unknown error" << endl;
			ts.ignore(print);
		}
	}
}

// handles fatal errors
int main() 
{
	try 
	{
		calculate();
		return 0;
	}
	catch (exception& e) 
	{
		cerr << "fatal error: " << e.what() << endl;
		return 1;
	}
	catch (...) 
	{
		cerr << "unknown fatal error\n";
		return 2;
	}
}


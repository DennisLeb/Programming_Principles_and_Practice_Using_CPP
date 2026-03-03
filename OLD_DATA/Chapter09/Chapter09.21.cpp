// 02/03/2026
// Chapter09.21.cpp
// Exercises

//
// [25] Add a command 'from x' to the calculator from Chapter 6 that makes it take input from a file 'x'.
//		Add a command 'to y' to the calculator that makes it write its output (both standart output and error output) to file 'y'.
//		Write a collection of test cases bases on ideas from §6.3 and use that to test the calculator.
//		Discuss how you would use these commands for testing.
//		
//		Ans:
//			All test inputs can be found in the input file (Chapter09.21.1.txt).
//			They are designed to test each feature that this version of the calculator provides.
//			One of them even causes a Token error, which is handled correctly as well.
// 
//			These commands are particularly useful for defining large amounts of variables, that can be read easily using the 'from x' command and then used in the application.
//			The 'to y' command could be used to compare results between users.
//

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

const char fin = 'I';
const string finkey = "from";

const char fout = 'O';
const string foutkey = "to";

const char reset = 'R';
const string resetkey = "reset";

/**************************************************************************************************/
/*										OTHER GLOBAL VALUES										  */
/**************************************************************************************************/

bool input_from_file = false;
bool output_to_file = false;

ifstream ifs;
ofstream ofs;

/**************************************************************************************************/
/*										CLASS DEFINITIONS										  */
/**************************************************************************************************/

// Token used to organize input
class Token 
{
public:
	Token(char ch) :kind(ch), value(0) {}					// three separate constructor functions
	Token(char ch, double val) :kind(ch), value(val) {}
	Token(char ch, string n) :kind(ch), name(n) {}
	char kind;					// what kind of Token
	double value = 0.0;			// numeric Token 
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
	if (full) 
	{			// checks buffer first
		full = false;
		return buffer;
	}

	char ch = 0;
	do 
	{
		(input_from_file ? ifs >> noskipws >> ch : cin >> noskipws >> ch);	// the noskipws flag lets cin read whitespace (spaces, tabs and newlines)
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
		
		(input_from_file ? ifs >> ch : cin >> ch);
		
		if (ch == '\n')		// is it the last expression before newline input?
			final_input = true;
		else
			final_input = false;

		(input_from_file ? ifs.putback(ch) : cin.putback(ch));
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
	case '9': 
	{
		(input_from_file ? ifs.putback(ch) : cin.putback(ch));	// puts number char into buffer
		double val;
		(input_from_file ? ifs >> val : cin >> val);	// gets entire number, not just one char					
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
			while ((input_from_file ? ifs.get(ch) : cin.get(ch)) && (isalpha(ch) || isdigit(ch) || ch == '_' || ch == '.'))
				s += ch;
			(input_from_file ? ifs.putback(ch) : cin.putback(ch));

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

			if (s == finkey)
				return Token{ fin };

			if (s == foutkey)
				return Token{ fout };

			if (s == resetkey)
				return Token{ reset };

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
	while ((input_from_file ? ifs >> ch : cin >> ch))
		if (ch == c)
			return;
}

// for run-time variable definition
class Variable 
{
public:
	Variable(string n, double v, bool b) :name(n), value(v), is_const(b) {}
	string name;
	double value;
	bool is_const;
};

// for managing variables
class Symbol_table 
{
public:
	double get(string s);
	void set(string s, double d);
	bool isDeclared(string s);
	double declare(string var, double val, bool is_const);

private:
	vector<Variable> var_table;
};

// read value of a defined variable
double Symbol_table::get(string s) 
{
	for (int i = 0; i < var_table.size(); ++i)	// searches vector until s is found
		if (var_table[i].name == s)
			return var_table[i].value;

	error(s, " is an undefined name - Symbol_table::get()");
	return NULL;		// This will never return, I just needed the compiler to shut up
}

// change value of a defined variable
void Symbol_table::set(string s, double d) 
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
double Symbol_table::declare(string var, double val, bool is_const) 
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

double expression();	// lets primary() call expression()
double primary();		// lets getPow() and getSqrt() call primary()

// handles syntax for standard library sqrt() implementation — sqrt(x)
double getSqrt() 
{
	Token t = ts.get();
	if (t.kind != '(') 
	{
		ts.putback(t);
		error("'(' expected - getSqrt()");
	}

	ts.putback(t);			// put '(' back to have primary() return the in-parentheses expression
	double d = primary();
	if (d < 0)
		error("negative square root - getSqrt()");

	return sqrt(d);
}

// handles syntax for standard library pow() implementation — pow(x, i)
double getPow() 
{
	Token t = ts.get();
	if (t.kind != '(') 
	{
		ts.putback(t);
		error("'(' expected - getPow()");
	}
	double x = expression();		// for pow(x, i), x should be an expression  

	t = ts.get();
	if (t.kind != ',') 
	{
		ts.putback(t);
		error("',' expected - getPow()");
	}

	int i = narrow<int>(primary());
	if (i == 0)
		return 1;

	t = ts.get();
	if (t.kind != ')') 
	{
		ts.putback(t);
		error("')' expected - getPow()");
	}

	return pow(x, i);
}

// handles primarys
double primary() 
{
	Token t = ts.get();
	switch (t.kind) 
	{
	case number:
		return t.value;

	case '(': 
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') 
		{
			ts.putback(t);
			error("')' expected - primary()");
		}
		return d;
	}

	case '-':					// unary minus prefix
		return -primary();

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
			double d = expression();
			st.set(t_name, d);	// assign new value to t_name variable
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
double term() 
{
	double left = primary();
	while (true) 
	{
		Token t = ts.get();
		switch (t.kind) 
		{
		case '*':
			left *= primary();
			break;

		case '/': 
		{
			double d = primary();
			if (d == 0) error("divide by zero - term()");
			left /= d;
			break;
		}

		case '%': 
		{
			int i1 = narrow<int>(left);
			int i2 = narrow<int>(primary());
			if (i2 == 0)
				error("% divide by zero - term()");
			left = i1 % i2;
			t = ts.get();
			break;
		}

		default:
			ts.putback(t);
			return left;
		}
	}
}

// handles expressions (+, -)
double expression() 
{
	double left = term();
	while (true) 
	{
		Token t = ts.get();
		switch (t.kind) 
		{
		case '+':
			left += term();
			break;

		case '-':
			left -= term();
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
double declaration() 
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

	double d = expression();
	st.declare(name, d, is_const);
	return d;
}

/**************************************************************************************************/
/*										CORE FUNCTION CALLS										  */
/**************************************************************************************************/

// checks for declaration keyword (let)
double statement() 
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
	ifs.exceptions(ifs.exceptions() | ios::eofbit);		// throw exception for eofbit
	ifs.exceptions(ifs.exceptions() | ios::failbit);	// and failbit
	ifs.exceptions(ifs.exceptions() | ios::badbit);		// and badbit
	cout << "Type \"help\" for instructions.\n" << endl;
	while (true)
		try 
		{
			if (ts.final_input && !input_from_file)		// only output prompt if all previous results were output and input comes from console
				cout << prompt;

			Token t = ts.get();
			while (t.kind == print)		// first discard all "prints"
				t = ts.get();

			if (t.kind == help) 
			{
				cout << "\t\t***    How to use   ***\n" << endl;
				cout << "Enter any expressions using the following operators:  +, -, *, /" << endl;
				cout << "Enter any integer expressions using the following operator:  %\n" << endl;
				cout << "There are also the functions pow() and sqrt():" << endl;
				cout << "pow(x, i) - with i being any integer" << endl;
				cout << "sqrt(x) - with x being any non-negative number\n" << endl;
				cout << "Additionally you may define your own variables using the following syntax: \"let\" NAME \"=\" EXPRESSION" << endl;
				cout << "For defining constants, you may add the const keyword after the let keyword.\n" << endl;
				cout << "The following constants have been pre-defined: pi = 3.1415926535, e = 2.7182818284\n" << endl;
				cout << "You may also read files into the calculator using the following syntax: \"from\" FILE_NAME" << endl;
				cout << "Any declared variables from the file will carry over into the current program instance.\n" << endl;
				cout << "To output into a file, you may use the folling syntax: \"to\" FILE_NAME\n" << endl;
				cout << "Type \"reset\" to reset your I/O settings back to default (console).\n" << endl;
				cout << "Separate each expression with ';'. Hit Enter to confirm your input.\n" << endl;
				cout << "Type \"quit\" to quit the program.\n" << endl;
				continue;
			}

			if (t.kind == quit)
				return;

			if (t.kind == reset)
			{
				input_from_file = false;
				output_to_file = false;
				if (ifs.is_open())
					ifs.close();
				if (ofs.is_open())
					ofs.close();
				cout << "I/O reset!" << endl;
				continue;
			}

			if (t.kind == fin)
			{
				if (!input_from_file)
				{
					t = ts.get();
					if (t.kind != name)
						error("invalid file name");

					ifs.open(t.name);
					if (!ifs)
						error("unable to open input file");

					input_from_file = true;
					cout << "Reading input file..." << endl;
					continue;
				}
				else
					error("input already comes from file");
			}

			if (t.kind == fout)
			{
				if (!output_to_file)
				{
					t = ts.get();
					if (t.kind != name)
						error("invalid file name");

					ofs.open(t.name);
					if (!ofs)
						error("unable to open output file");

					output_to_file = true;
					cout << "Output now goes to file!" << endl;
					continue;
				}
				else
					error("output already goes to file");
			}

			ts.putback(t);
			if (output_to_file)
				ofs << result << statement() << endl;

			else
				cout << result << statement() << endl;
			
		}
	catch (ifstream::failure& e) 
	{
		if (!ifs && !ifs.eof())
			error("ifstream failure");

		ifs.close();
		input_from_file = false;

		(output_to_file ? ofs << "end of input file reached" << endl : cerr << "end of input file reached" << endl);
		ts.ignore(print);
	}
	catch (exception& e) 
	{
		(output_to_file ? ofs << "error: " << e.what() << endl : cerr << "error: " << e.what() << endl);
		ts.ignore(print);
	}
	catch (...) 
	{
		(output_to_file ? ofs << "unknown error" << endl : cerr << "unknown error" << endl);
		ts.ignore(print);
	}
}

// handles fatal errors
int main() 
{
	try 
	{
		// predefine names
		st.declare("pi", 3.1415926535, true);
		st.declare("e", 2.7182818284, true);

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

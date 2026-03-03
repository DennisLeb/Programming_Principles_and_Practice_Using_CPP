// 26/02/2026
// Chapter09.17.cpp
// Exercises

//
// [21] Define a Roman_int class for holding Roman numerals (as ints) with a << and >>.
//		Provide Roman_int with an as_int() member that returns the int value, so that if r is a Roman_int,
//		we can write cout << "Roman " << r << " equals " << r.as_int() << '\n';.
//

/*
*	[I = 1; V = 5; X = 10; L = 50; C = 100; D = 500; M = 1000]	
* 
*	Rules for Roman numerals (from 'I' to 'M')
*
*	1. Only 'I', 'X', and 'C' may precede a numeral of greater value.
*
*	2. Whenever one numeral precedes another of greater value, the greater must at most rank up to two ranks above the lesser.
*
*		Examples:
*			'I' may only precede 'V' or 'X'
*			'X' may only precede 'L' or 'C'
*			'C' may only precede 'D' or 'M'
* 
*	3. Whenever a preceding numeral, as well as both numerals it could potentially precede are present, it must precede that of lesser value.
* 
*		Examples:
*			14 must be expressed as "XIV", and never as "IXV"
*			140 must be expressed as "CXL", and never as "XCL"
*			...
* 
*	4. Only 'I', 'X', and 'C' may appear more than once in one Roman value. They may only repeat up to three times.
* 
*	5. A repeating element in a Roman value may only occur, if that numeral does not precede one of greater value.
*/

#include "PPPheaders.h"

/**************************************************************************************************/
/*												CLASS											  */
/**************************************************************************************************/

class Roman_int
{
public:
	Roman_int() :decimal_num{ 0 }, rom_num{ "" } {}
	Roman_int(const string& rom) :rom_num{ rom } 
	{
		this->decimal_num = conv_to_int(rom);
	}
	Roman_int(const unsigned int& num) :decimal_num{ num }
	{
		if (num > 1000 || num == 0)
			error("only values between 1 and 1000 are allowed");
		this->rom_num = conv_to_rom(num);
	}

	unsigned int as_int() const { return decimal_num; }
	string as_rom() const { return rom_num; }

private:
	unsigned int conv_to_int(const string&);
	string conv_to_rom(unsigned int);

	unsigned int decimal_num;
	string rom_num;
};

/**************************************************************************************************/
/*											OPERATOR OVERLOADING								  */
/**************************************************************************************************/

ostream& operator<<(ostream& os, const Roman_int& r) { return os << r.as_rom(); }

istream& operator>>(istream& is, Roman_int& r)
{
	char ch = '\0';
	is >> ch;
	if (!is)
		return is;

	if (isdigit(ch))
	{
		is.unget();
		unsigned int num = 0;
		is >> num;
		r = Roman_int{ num };
		return is;
	}
	if (isalpha(ch))
	{
		is.unget();
		string rom_num;
		is >> rom_num;
		r = Roman_int{ rom_num };
		return is;
	}
	is.clear(ios::failbit);
	return is;
}

/**************************************************************************************************/
/*											UTILITY FUNCTIONS									  */
/**************************************************************************************************/

									/**		conv_to_int		**/
									/*************************/
unsigned int getDecimalFromRoman(const char& num)
{
	switch (num)
	{
	case 'I':
		return 1;
	case 'V':
		return 5;
	case 'X':
		return 10;
	case 'L':
		return 50;
	case 'C':
		return 100;
	case 'D':
		return 500;
	case 'M':
		return 1000;
	default:
		error("invalid roman numeral -> getDecimalFromRoman()");
		return NULL;	// Gets compiler to shut up
	}
}

bool isRepeatableNumeral(const int& num)
{
	switch (num)
	{
	case 1: case 10: case 100:
		return true;
	default:
		return false;
	}
}

unsigned int getNumeralCount(const string& rom_num, const int& num, const string::const_iterator& it)
{
	if ((it + 1) != rom_num.end() && getDecimalFromRoman(*(it + 1)) == num)
		return (getNumeralCount(rom_num, num, it + 1) + 1);
	return 1;
}

int isValidPrecedingRoman(const string& rom_num, const int& prec_val, const int& next_val)
{
	// 1. Only 'I', 'X', and 'C' may precede a numeral of greater value.
	switch (prec_val)
	{
	case 1:
		// 2. Whenever one numeral precedes another of greater value, the greater must only rank up to two ranks above the lesser.
		if (next_val != 5 && next_val != 10)
			return 0;
		// 3. Whenever a preceding numeral, as well as both numerals it could potentially precede are present, it must precede that of lesser value.
		if (next_val == 10 && rom_num.find('V') != string::npos)
			return 0;
		break;
			
	case 10:
		if (next_val != 50 && next_val != 100)
			return 0;
		if (next_val == 100 && rom_num.find('L') != string::npos)
			return 0;
		break;
			
	case 100:
		if (next_val != 500 && next_val != 1000)
			return 0;
		if (next_val == 1000 && rom_num.find('D') != string::npos)
			return 0;
		break;
			
	default:
		return 0;
	}
	return -prec_val;
}

int isValidRepeatingRoman(const string& rom_num, const unsigned int& rep_val, string::const_iterator& it)
{
	unsigned int ctr = 0;
	// 4. Only 'I', 'X', and 'C' may appear more than once in one Roman value. They may only repeat up to three times.
	if (!isRepeatableNumeral(rep_val) || (ctr = getNumeralCount(rom_num, rep_val, it)) > 3)
		return 0;

	// 5. A repeating element in a Roman value may only occur, if that numeral does not precede one of greater value.
	else if ((it + ctr) < rom_num.end() /* Prevent range-error */ && rep_val < getDecimalFromRoman(*(it + ctr)) /* Val at end of repetition must not be greater */ )
		return 0;

	// If valid repetition occurs, set iterator to the element after. Subtract by one because outside for-loop increments by one.
	if (it + ctr <= rom_num.end() - 1 /* Prevent range-error */ )
		it += ctr - 1;
	else
		it = rom_num.end() - 1;

	return ctr;
}

									/**		conv_to_rom		**/
									/*************************/
char getRomanFromDecimal(const int& num)
{
	switch (num)
	{
	case 1:
		return 'I';
	case 5:
		return 'V';
	case 10:
		return 'X';
	case 50:
		return 'L';
	case 100:
		return 'C';
	case 500:
		return 'D';
	case 1000:
		return 'M';
	default:
		error("invalid decimal number -> getRomanFromDecimal()", num);
		return NULL;	// Gets compiler to shut up
	}
}

void appendDecimalToRoman(unsigned int& decimal_num, string& rom_num, const unsigned int& i)
{
	char temp_ch = '\0';
	string temp_str;
	for (int cntr = 1; decimal_num >= i; ++cntr)
	{
		temp_ch = getRomanFromDecimal(i);
		if (cntr != 4 /* Were there 4 repetitions? */)
		{
			temp_str += temp_ch;
			decimal_num -= i;
			continue;
		}
		if (!rom_num.empty() /* Was there a previous numeral? */ && *(--rom_num.end()) == getRomanFromDecimal(i * 5) /* Should it replace the previous numeral? */)
		{
			rom_num.pop_back();
			temp_str.clear();
			temp_str += temp_ch;
			temp_str += getRomanFromDecimal(i * 10);	// Returns 'X', 'C', or 'M'
		}
		else
		{
			temp_str.clear();
			temp_str += temp_ch;
			temp_str += getRomanFromDecimal(i * 5);		// Returns 'V', 'L', or 'D'
		}
		decimal_num -= i;
	}
	rom_num += temp_str;
}

/**************************************************************************************************/
/*											MEMBER FUNCTIONS									  */
/**************************************************************************************************/

unsigned int Roman_int::conv_to_int(const string& rom_num)
{
	unsigned int sum = 0;
	int this_val = 0, next_val = 0;
	for (auto it = rom_num.begin(); it != rom_num.end(); ++it)
	{
		this_val = getDecimalFromRoman(*it);
		next_val = 0;

		if (it != --rom_num.end() /* Isn't last element */)
			next_val = getDecimalFromRoman(*(it + 1));

		// Handles rules 1-3
		if (this_val < next_val && !(this_val = isValidPrecedingRoman(rom_num, this_val, next_val)))
			error("invalid preceding Roman numeral");

		// Handles rules 4 and 5
		else if (this_val == next_val && !(this_val *= isValidRepeatingRoman(rom_num, this_val, it)) /* Multiply this_val by repetition counter to skip redundant loops (iterator modified inside function) */ )
			error("invalid repeating Roman numeral");

		sum += this_val;
	}
	if (sum > 1000)
		error("no values greater than 1000 allowed");
	return sum;
}

string Roman_int::conv_to_rom(unsigned int decimal_num)
{
	string rom_num;
	for (unsigned int i = 1000; i != 0 && decimal_num != 0; i /= 10)	// This does perform some redundant loops if decimal_num is small, but that's not too serious in this case.
	{
		appendDecimalToRoman(decimal_num, rom_num, i);
		if (i != 1 /* Don't pass 0 as an argument */ )
			appendDecimalToRoman(decimal_num, rom_num, (i / 2));
	}
	return rom_num;
}

/**************************************************************************************************/
/*												MAIN											  */
/**************************************************************************************************/

int main()
{
	try
	{
		Roman_int r;
		cout << "> ";
		cin >> r;
		cout << "\nRoman " << r << " equals " << r.as_int() << endl;
				
		// Uncomment to print 1-1000 in Roman numeral form
		/*
		for (unsigned int i = 0; i < 1000; ++i)
		{
			Roman_int rom{ i + 1 };
			cout << "Roman " << rom << " equals " << rom.as_int() << endl;
		}
		*/

		cout << "Success!" << endl;
		return 0;
	}
	catch (exception& e)
	{
		cerr << "error: " << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "unknown error" << endl;
		return 2;
	}
}

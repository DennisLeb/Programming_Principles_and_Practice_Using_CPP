// 11/02/2026
// Chapter08.05.cpp
// Exercises

//
// [13] Design and implement a rational number class, Rational. A rational number has two parts: a numerator and a denominator, for example, 5/6.
//		Provide assignment, addition, subtraction, multiplication, division, and equality operators. Also, provide a conversion to double.
//		Why would people want to use a Rational class?
//
//		Ans:
//			In many cases it's simpler to work with Rationals, instead of decimal fractions (doubles).
//			Having a thorough but tidy Rational class can remove unnecessary complications in some programs.
//

#include "PPPheaders.h"

/**************************************************************************************************/
/*										CLASS DEFINITION										  */
/**************************************************************************************************/

class Rational
{
public:
	/**************** Constructors ****************/
	/**********************************************/

	Rational() :numerator{ 0 }, denominator{ 0 } {}
	Rational(const int& num, const int& denom) :numerator{ num }, denominator{ denom }
	{
		if (!isValidRational(*this))
			error("invalid Rational");
	}

	/**************** Member Functions ****************/
	/**************************************************/

	// Return member values
	int getNumerator() const { return numerator; }
	int getDenominator() const { return denominator; }

private:
	// Validate
	bool isValidRational(const Rational& rat) { return (rat.getDenominator() != 0); }

	/**************** Member Variables ****************/
	/**************************************************/

	int numerator;
	int denominator;
};

/**************** Necessary forward-declarations ****************/
/****************************************************************/

Rational reduce(const Rational& rat);

/**************************************************************************************************/
/*									  OPERATOR OVERLOADING  									  */
/**************************************************************************************************/

// Output Rational
ostream& operator<<(ostream& os, const Rational& rat) { return os << rat.getNumerator() << '/' << rat.getDenominator(); }

// Equality
bool operator==(const Rational& rat_1, const Rational& rat_2) {	return (rat_1.getNumerator() == rat_2.getNumerator() && rat_1.getDenominator() == rat_2.getDenominator()); }

// Inequality
bool operator!=(const Rational& rat_1, const Rational& rat_2) {	return !(rat_1 == rat_2); }

// Divide Rational / Rational
Rational operator/(const Rational& rat_1, const Rational& rat_2)
{
	int num_1 = rat_1.getNumerator(), num_2 = rat_2.getNumerator();
	int denom_1 = rat_1.getDenominator(), denom_2 = rat_2.getDenominator();

	// Use reciprocal value (Kehrbruch) to divide
	int new_numerator = num_1 * denom_2;
	int new_denominator = num_2 * denom_1;

	return reduce(Rational{ new_numerator, new_denominator });;
}

// Divide Rational / int
Rational operator/(const Rational& rat_1, const int& number) { return (rat_1 / Rational{ number, 1 }); }

// Multiply Rational * Rational
Rational operator*(const Rational& rat_1, const Rational& rat_2)
{
	int num_1 = rat_1.getNumerator(), num_2 = rat_2.getNumerator();
	int denom_1 = rat_1.getDenominator(), denom_2 = rat_2.getDenominator();

	// Multiply nums and denoms
	int new_numerator = num_1 * num_2;
	int new_denominator = denom_1 * denom_2;

	return reduce(Rational{ new_numerator, new_denominator });
}

// Multiply Rational * int
Rational operator*(const Rational& rat_1, const int& number) { return (rat_1 * Rational{ number, 1 }); }

// Add Rational + Rational
Rational operator+(const Rational& rat_1, const Rational& rat_2)
{
	int num_1 = rat_1.getNumerator(), num_2 = rat_2.getNumerator();
	int denom_1 = rat_1.getDenominator(), denom_2 = rat_2.getDenominator();

	// Find common denominator and add together
	int new_denominator = denom_1 * denom_2;
	int new_numerator = (num_1 * denom_2) + (denom_1 * num_2);

	return reduce(Rational{ new_numerator, new_denominator });
}

// Add Rational + int
Rational operator+(const Rational& rat_1, const int& number) { return (rat_1 + Rational{ number, 1 }); }

// Subtract Rational - Rational
Rational operator-(const Rational& rat_1, const Rational& rat_2)
{
	int num_1 = rat_1.getNumerator(), num_2 = rat_2.getNumerator();
	int denom_1 = rat_1.getDenominator(), denom_2 = rat_2.getDenominator();
	int new_denominator = 0, new_numerator = 0;

	// Find common denominator and subtract
	if (denom_1 != denom_2)
	{
		new_denominator = denom_1 * denom_2;
		new_numerator = (num_1 * denom_2) - (denom_1 * num_2);
	}
	else
	{
		new_denominator = denom_1;
		new_numerator = num_1 - num_2;
	}

	return reduce(Rational{ new_numerator, new_denominator });
}

// Subtract Rational - int
Rational operator-(const Rational& rat_1, const int& number) { return (rat_1 - Rational{ number, 1 }); }

/**************************************************************************************************/
/*									  HELPER FUNCTIONS/OTHER  									  */
/**************************************************************************************************/

// Performs recursion to find GCD using basic Euclidean algorithm
int findGCD(int a, int b)
{
	// Euclidean algorithm source: https://www.geeksforgeeks.org/dsa/euclidean-algorithms-basic-and-extended/

	if (a == 0)
		return b;
	return findGCD(b % a, a);
}

// Reduce to greatest common divisor
Rational reduce(const Rational& rat)
{
	int num = rat.getNumerator(), denom = rat.getDenominator();
	int greatest_common_divisor = findGCD(num, denom);

	return Rational{ num / greatest_common_divisor, denom / greatest_common_divisor };
}

double ratToDouble(const Rational& rat) { return ((double)rat.getNumerator() / (double)rat.getDenominator()); }

/**************************************************************************************************/
/*											 MAIN        										  */
/**************************************************************************************************/

int main()
{
	try
	{
		Rational rat_1{ 2, 4 };
		Rational rat_2{ 2, 4 };
		Rational rat_3 = rat_1 * rat_2;

		if (rat_1 == rat_2)
			cout << rat_1 << " is equal to " << rat_2 << '\n' << endl;
		else if (rat_1 != rat_2)
			cout << rat_1 << " is not equal to " << rat_2 << '\n' << endl;

		cout << "Result: " << rat_3 << endl;
		cout << "Result (double): " << ratToDouble(rat_3) << endl;
		
		return 0;
	}
	catch (exception& e)
	{
		cerr << "error: " << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "unknown error: " << endl;
		return 2;
	}
}

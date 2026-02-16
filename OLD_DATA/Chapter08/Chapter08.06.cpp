// 12/02/2026
// Chapter08.06.cpp
// Exercises

//
// [14] Design and implement a Money class for calculations involving dollars and cents.
//		Arithmetic has to be accurate to the last cent using the 4/5 rounding rule (.5 of a cent rounds up; anything less rounds down).
//		Represent a monetary amount as a number of cents in a long int, but input and output as dollars and cents, e.g., $123.45.
//		Do not worry about amounts that don't fit into a long int.
//
// [15] Refine the Money class by adding a currency. Don't accept illegal operations.
//		For example, adding USD and DKK together only works if you provide a conversion table, defining the conversion factor between currencies.
//
// [16] Define an input operator (>>) that reads monetary amounts with currency denominations, such as USD1.23 and DKK5.00, into a Money variable.
//		Also define a corresponding output operator (<<).
//
// [17] Give an example of a calculation where a Rational gives a mathematically better result than a Money.
//		Ans:
//			Any calculation where currency is not a factor, for example if you wanted to teach kids about rational numbers in school exercises.
// 
// [18] Give an example of a calculation where a Rational gives a mathematically better result than a double.
//		Ans:
//			Any calculation where Rationals can be precise enough to produce accurate results and don't have to keep track of many decimal places.
//			E.g. a calculation of how to divide a pizza between friends.
//


#include "PPPheaders.h"

/**************************************************************************************************/
/*										CLASS DEFINITION										  */
/**************************************************************************************************/

class Money
{
public:
	enum Currency
	{
		USD, EUR, DKK		// American Dollar, Euro, Danish Kroner
	};

	// Constructors
	Money() :minor_currency{ 0 }, major_currency{ 0 }, currency{ USD } {}
	Money(const double& maj_cur, const Currency& target_cur) :minor_currency{ (long)(round(maj_cur * 100)) }, major_currency{ round(maj_cur * 100) / 100 }, currency{ target_cur } {}

	// Return member values
	long getMinorCur() const { return minor_currency; }
	double getMajorCur() const { return major_currency; }
	Currency getCurrency() const { return currency; }
	string getCurrencyString() const;

	// Change member values
	void convertCurrency(const Currency& target_cur);
	void setMajorCur(const double& maj_cur) { major_currency = maj_cur; }
	void setCurrency(string);

	// Input Money
	friend istream& operator>>(istream& is, Money& mon)
	{
		char cur_ch;
		string cur_str;
		for (int i = 0;  i < 3 && (cur_ch = is.get()); ++i)	// only reads 3 chars for currency
			cur_str += cur_ch;

		mon.setCurrency(cur_str);
		return is >> mon.major_currency;
	}

private:
	// Member values
	long minor_currency;	// e.g. cents
	double major_currency;	// e.g. dollars

	Currency currency;
};

/**************************************************************************************************/
/*									  OPERATOR OVERLOADING  									  */
/**************************************************************************************************/

// Output Money
ostream& operator<<(ostream& os, const Money& mon) { return os << mon.getCurrencyString() << mon.getMajorCur(); }

// Add Money + Money (will convert result to first argument's currency if currencies are unequal)
Money operator+(const Money& mon_1, const Money& mon_2)
{
	if (mon_1.getCurrency() != mon_2.getCurrency())
	{
		Money temp_mon = mon_2;
		temp_mon.convertCurrency(mon_1.getCurrency());
		return (Money{ mon_1.getMajorCur() + temp_mon.getMajorCur(), mon_1.getCurrency()});
	}
	else
		return (Money{ mon_1.getMajorCur() + mon_2.getMajorCur(), mon_1.getCurrency()});
}

// Subtract Money - Money (will convert result to first argument's currency if currencies are unequal)
Money operator-(const Money& mon_1, const Money& mon_2)
{
	if (mon_1.getCurrency() != mon_2.getCurrency())
	{
		Money temp_mon = mon_2;
		temp_mon.convertCurrency(mon_1.getCurrency());
		return (Money{ mon_1.getMajorCur() - temp_mon.getMajorCur(), mon_1.getCurrency()});
	}
	else
		return (Money{ mon_1.getMajorCur() - mon_2.getMajorCur(), mon_1.getCurrency()});
}

// Multiply Money * Money (will convert result to first argument's currency if currencies are unequal)
Money operator*(const Money& mon_1, const Money& mon_2)
{
	if (mon_1.getCurrency() != mon_2.getCurrency())
	{
		Money temp_mon = mon_2;
		temp_mon.convertCurrency(mon_1.getCurrency());
		return (Money{ mon_1.getMajorCur() * temp_mon.getMajorCur(), mon_1.getCurrency()});
	}
	else
		return (Money{ mon_1.getMajorCur() * mon_2.getMajorCur(), mon_1.getCurrency()});
}

// Divide Money / Money (will convert result to first argument's currency if currencies are unequal)
Money operator/(const Money& mon_1, const Money& mon_2)
{
	if (mon_1.getCurrency() != mon_2.getCurrency())
	{
		Money temp_mon = mon_2;
		temp_mon.convertCurrency(mon_1.getCurrency());
		return (Money{ mon_1.getMajorCur() / temp_mon.getMajorCur(), mon_1.getCurrency()});
	}
	else
		return (Money{ mon_1.getMajorCur() / mon_2.getMajorCur(), mon_1.getCurrency()});
}

/**************************************************************************************************/
/*									OUTSIDE-CLASS DEFINITIONS  									  */
/**************************************************************************************************/

// Returns Currency string
string Money::getCurrencyString() const
{
	switch (this->currency)
	{
	case USD:
		return "USD";
	case EUR:
		return "EUR";
	case DKK:
		return "DKK";
	default:
		error("getCurrencyString()");
		return NULL;	// Gets compiler to shut up
	}
}

// Converts amount and currency of Money object (exchange rates: 12/02/2026)
void Money::convertCurrency(const Currency& target_cur)
{
	// This is incredibly ugly
	switch (this->currency)
	{
	case USD:
		switch (target_cur)
		{
		case USD:
			error("Already USD!");
			break;
		case EUR:
			this->minor_currency = (long)round((double)minor_currency * .84);
			this->major_currency = (double)minor_currency / 100.0;
			this->currency = EUR;
			return;
		case DKK:
			this->minor_currency = (long)round((double)minor_currency * 6.29);
			this->major_currency = (double)minor_currency / 100.0;
			this->currency = DKK;
			return;
		}
		break;

	case EUR:
		switch (target_cur)
		{
		case USD:
			this->minor_currency = (long)round((double)minor_currency * 1.19);
			this->major_currency = (double)minor_currency / 100.0;
			this->currency = USD;
			return;
		case EUR:
			error("Already EUR!");
			break;
		case DKK:
			this->minor_currency = (long)round((double)minor_currency * 7.47);
			this->major_currency = (double)minor_currency / 100.0;
			this->currency = DKK;
			return;
		}
		break;

	case DKK:
		switch (target_cur)
		{
		case USD:
			this->minor_currency = (long)round((double)minor_currency * .16);
			this->major_currency = (double)minor_currency / 100.0;
			this->currency = USD;
			return;
		case EUR:
			this->minor_currency = (long)round((double)minor_currency * .13);
			this->major_currency = (double)minor_currency / 100.0;
			this->currency = EUR;
			return;
		case DKK:
			error("Already DKK!");
		}
		break;

	default:
		error("convertCurrency()");
	}
}

// Set currency with string arg
void Money::setCurrency(string cur_str)
{
	// Again, quite ugly. Have to look for a better way to deal with enums.
	if (cur_str == "USD")
		this->currency = Money::Currency::USD;
	else if (cur_str == "EUR")
		this->currency = Money::Currency::EUR;
	else if (cur_str == "DKK")
		this->currency = Money::Currency::DKK;
	else
		error("invalid currency string; setCurrency()");
}

/**************************************************************************************************/
/*											 MAIN        										  */
/**************************************************************************************************/

int main()
{
	try
	{
		Money mon_1{ 10.00, Money::Currency::USD };
		Money mon_2{ 212.872, Money::Currency::USD };

		cout << "Money: " << mon_1 << endl;
		cout << "Money: " << mon_2 << '\n' << endl;

		cout << "Sum: " << mon_1 + mon_2 << endl;
		cout << "Difference: " << mon_1 - mon_2 << endl;
		cout << "Product: " << mon_1 * mon_2 << endl;
		cout << "Quotient: " << mon_1 / mon_2 << endl;

		Money mon_3{};
		cin >> mon_3;
		cout << mon_3 << endl;

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

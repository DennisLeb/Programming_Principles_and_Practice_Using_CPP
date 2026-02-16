// 10/02/2026
// Chapter08.04.cpp
// Exercises

//
// [12] Change the representation of Date to be the number of days since January 1, 1970 (known as day 0), represented as a long int,
//      and re-implement the Date member functions from §8.4.2.
//      Reject dates outside the range we can represent that way, also reject days before day 0, i.e., no negative days.
//

#include "PPPheaders.h"

/**************************************************************************************************/
/*										   CONSTANTS											  */
/**************************************************************************************************/

constexpr int day_0_year = 1970;
constexpr int day_0_month = 1;
constexpr int day_0_day = 1;

/**************************************************************************************************/
/*										CLASS DEFINITION										  */
/**************************************************************************************************/

class Date
{
public:
	// Year and Day serve no real purpose, they just improve readability
	struct Year
	{
		Year() :y{ 0 } {}
		Year(int yy) :y{ yy } {}
		int y;
	};

	enum class Month
	{
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	struct Day
	{
		Day() :d{ 0 } {}
		Day(int dd) :d{ dd } {}
		int d;
	};

	/**************** Constructors ****************/
	/**********************************************/

	// construct day 0
	Date() :y{ day_0_year }, m{ day_0_month }, d{ day_0_day }, days_since_day_0{ 0 } {}

	// construct Date from days_since_day_0
	Date(const long long& passed_days)
	{
		if (!isValidPassedDays(passed_days))
			error("invalid Date");
		
		days_since_day_0 = narrow<long>(passed_days);

		// assigns y, m, and d
		calculateDate(days_since_day_0);
		return;
	}

	// construct days_since_day_0 from Date
	Date(const Year&, const Month&, const Day&);

	/**************** Member Functions ****************/
	/**************************************************/

	// return member values
	int getYear() const { return y.y; }
	Month getMonth() const { return m; }
	int getDay() const { return d.d; }
	long getPassedDays() const { return days_since_day_0; }

private:
	void calculateDate(long passed_days);

	// validate
	const bool isValidDate(const Year& yy, const Month& mm, const Day& dd) const;
	const bool isValidMonth(const Month& mm) const { return (Month::jan <= mm && mm <= Month::dec); }
	const bool isValidDay(const bool&, const Month&, const Day&) const;
	
	const bool isValidPassedDays(const long long& passed_days) const;

	/**************** Member Variables ****************/
	/**************************************************/

	Year y;
	Month m;
	Day d;
	long days_since_day_0;
};

/**************** Necessary forward-declarations ****************/
/****************************************************************/

int getDayCount(const Date::Month&, const bool&);
const bool leapyear(const Date::Year& yy);
void calculateYear(Date::Year&, long&);
void calculateMonth(const bool&, Date::Month&, long&);

/**************************************************************************************************/
/*									  OPERATOR OVERLOADING  									  */
/**************************************************************************************************/

/**************** Year ****************/
/**************************************/

// adds ++Y
Date::Year operator++(Date::Year& Y) { return ++Y.y; }

// adds --Y
Date::Year operator--(Date::Year& Y) { return --Y.y; }

/**************** Month ****************/
/***************************************/

// adds ++M
Date::Month operator++(Date::Month& M)
{
	M = (M == Date::Month::dec) ? (Date::Month::jan) : (Date::Month{ static_cast<int>(M) + 1 });
	return M;
}

// adds --M
Date::Month operator--(Date::Month& M)
{
	M = (M == Date::Month::jan) ? (Date::Month::dec) : (Date::Month{ static_cast<int>(M) - 1 });
	return M;
}

/**************** Day ****************/
/*************************************/

// adds d + int
Date::Day operator+=(Date::Day& D, int i) { return (D.d += i); }

// adds d % int
Date::Day operator%(Date::Day& D, int i) { return (D.d %= i); }

/**************** Date ****************/
/**************************************/

// print Date data
ostream& operator<<(ostream& os, const Date& date)
{
	os << "Date: " << date.getDay() << '/' << static_cast<int>(date.getMonth()) << '/' << date.getYear() << endl;

	return os;
}

// get difference between Dates in days
long operator-(const Date& date_1, const Date& date_2)
{
	long difference = 0;
	int date_year_1 = date_1.getYear(), date_year_2 = date_2.getYear();
	if (date_year_1 > date_year_2)
	{
		while (date_year_1 != date_year_2)	// has to loop because of leap years? Surely there's a better solution
		{
			difference -= (leapyear(date_year_1) ? 366 : 365);
			--date_year_1;
		}
	}
	else if (date_year_1 < date_year_2)
	{
		while (date_year_1 != date_year_2)
		{
			difference += (leapyear(date_year_1) ? 366 : 365);
			++date_year_1;
		}
	}	// date_year_1 == date_year_2 just continues
	
	bool is_leap_year = leapyear(date_year_1);	// year no longer changes
	Date::Month date_month_1 = date_1.getMonth(), date_month_2 = date_2.getMonth();
	if (date_month_1 > date_month_2)
	{
		while (date_month_1 != date_month_2)
		{
			difference -= (long)getDayCount(date_month_1, is_leap_year);		// getDayCount() checks for leap years
			--date_month_1;
		}
	}
	else if (date_month_1 < date_month_2)
	{
		while (date_month_1 != date_month_2)
		{
			difference += (long)getDayCount(date_month_1, is_leap_year);		// widening conversion, should be fine
			++date_month_1;
		}
	}	// date_month_1 == date_month_2 just continues

	difference -= date_1.getDay() - date_2.getDay();
	return difference;
}

/**************************************************************************************************/
/*									OUTSIDE-CLASS DEFINITIONS  									  */
/**************************************************************************************************/

// construct days_since_day_0 from Date
Date::Date(const Year& yy, const Month& mm, const Day& dd) :y{ yy }, m{ mm }, d{ dd }
{
	if (!isValidDate(yy, mm, dd))
		error("invalid Date");
			
	Date day_0{};
	days_since_day_0 = day_0 - *this;	// *this accesses this Date object (Year, Month, and Day)
}

const bool Date::isValidDate(const Year& yy, const Month& mm, const Day& dd) const { return isValidMonth(mm) && isValidDay(leapyear(yy), mm, dd); }

// takes leap years and month into account to determine whether a day is valid
const bool Date::isValidDay(const bool& is_leap_year, const Date::Month& month, const Date::Day& day) const
{
	if (day.d >= 1 && day.d <= getDayCount(month, is_leap_year))
		return true;

	error("invalid Day");
	return NULL;	// will never return, makes compiler shut up though
}

// uses long long (_int64)'s increased size to reject large values
const bool Date::isValidPassedDays(const long long& passed_days) const
{
	if (passed_days > LONG_MAX || passed_days < 0)
		return false;
	else
		return true;
}

// calculates Date from Days since day 0
void Date::calculateDate(long passed_days)
{
	const Date start_date{};					// initialized to January 1, 1970 (day 0)
	Year date_year = start_date.getYear();
	Month date_month = start_date.getMonth();
	Day date_day = start_date.getDay();

	calculateYear(date_year, passed_days);
	
	if (passed_days == 0)
	{
		y = date_year;
		m = date_month;
		d = date_day;
		return;
	}

	calculateMonth(leapyear(date_year), date_month, passed_days);	// only handles one Year, so leapyear() is executed only once

	if (passed_days != 0)
		date_day += passed_days;
	
	y = date_year;
	m = date_month;
	d = date_day;
	return;
}

/**************************************************************************************************/
/*									  HELPER FUNCTIONS/OTHER  									  */
/**************************************************************************************************/

// adds to Year value and subtracts from Day value (leap years accounted for)
void calculateYear(Date::Year& year, long& passed_days)
{
	bool is_leap_year = false;
	while (passed_days >= ((is_leap_year = leapyear(year)) ? 366 : 365))	// assigns is_leap_year and loops if passed_days has equal to or over a year left
	{
		if (!is_leap_year)
			passed_days -= 365;
		else
			passed_days -= 366;

		++year;
	}
	return;
}

// adds to Month value and subtracts from Day value (leap years accounted for)
void calculateMonth(const bool& is_leap_year, Date::Month& month, long& passed_days)
{
	while (passed_days >= 28)	// lowest possible Day per Month value == 28
	{
		int day_count = getDayCount(month, is_leap_year);
		if (passed_days >= day_count)
			passed_days -= day_count;
		else
			break;	// occurs if (28 <= passed_days < 31)
		
		++month;
	}
}

// return true if year is divisible by 4 and not 100, or if it is divisible by 400
const bool leapyear(const Date::Year& yy) { return ((yy.y % 4 == 0 && yy.y % 100 != 0) || yy.y % 400 == 0); }

// returns the Day count of the month argument, checking for leap years also
int getDayCount(const Date::Month& month, const bool& is_leap_year)
{
	switch (month)
	{
	// 31 day months
	case Date::Month::jan: case Date::Month::mar: case Date::Month::may:
	case Date::Month::jul: case Date::Month::aug: case Date::Month::oct: case Date::Month::dec:
		return 31;

	// 30 day months
	case Date::Month::apr: case Date::Month::jun: case Date::Month::sep: case Date::Month::nov:
		return 30;

	// February
	case Date::Month::feb:
	{
		if (is_leap_year)
			return 29;
		else
			return 28;
	}
	default:
		error("getDayCount()");
		return NULL;			// will never return, makes compiler shut up though
	}
}

// returns the weekday (0-6 with Sunday = 0) using Gauss's algorithm (Gregorian calendar)
int getWeekDay(const Date& date)
{
	// Gauss's algorithm source: https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Mathematical_algorithms

	// D = date.getDay(), m = month offset (depending on month and if it's a leap year), A = date.getYear()
	// week_day = (D + m + 5 * ((A-1) % 4) + 4 * ((A-1) % 100) + 6 * ((A-1) % 400)) % 7

	int D = date.getDay(), A = date.getYear();	// bad names, but in line with the algorithm's notation
	int m = 0;

	// find out m
	switch (static_cast<int>(date.getMonth()))
	{
	case 1:
		m = 0;
		break;
	case 2:
		m = 3;
		break;
	case 3: case 11:					// some months share offset values
		m = (leapyear(A) ? 4 : 3);		// differing offset value for leap years
		break;
	case 4: case 7:
		m = (leapyear(A) ? 0 : 6);
		break;
	case 5:
		m = (leapyear(A) ? 2 : 1);
		break;
	case 6:
		m = (leapyear(A) ? 5 : 4);
		break;
	case 8:
		m = (leapyear(A) ? 3 : 2);
		break;
	case 9: case 12:
		m = (leapyear(A) ? 6 : 5);
		break;
	case 10:
		m = (leapyear(A) ? 1 : 0);
		break;
	default:
		error("getWeekday()");
	}

	int week_day = (D + m + 5 * ((A - 1) % 4) + 4 * ((A - 1) % 100) + 6 * ((A - 1) % 400)) % 7;
	return week_day;
}

// returns the Date of the next day that isn't a Saturday or Sunday
Date nextWorkday(const Date& date)
{
	int current_workday = getWeekDay(date), days_until_workday = 0;

	// how many days left until next workday?
	switch (current_workday)
	{
	case 0: case 1: case 2: case 3: case 4:		// for sun-thu the next workday is tomorrow
		days_until_workday = 1;
		break;
	case 5:										// Friday
		days_until_workday = 3;
		break;
	case 6:										// Saturday
		days_until_workday = 2;
		break;
	default:
		error("nextWorkday()");
	}

	// get current date values
	int year = date.getYear();						// Year and Day object constructors take int
	Date::Month month = date.getMonth();
	int day = date.getDay();

	// calculate next workday date
	int day_count = getDayCount(month, leapyear(year));
	if ((day + days_until_workday) > day_count)	// does the sum exceed this month's day_count?
	{
		if (month == Date::Month::dec)	// increment month and year
		{
			Date next_workday{ ++year, ++month, (day + days_until_workday) % day_count };	// using % works because sum > day_count, returning 1-3
			return next_workday;
		}
		else  // increment month
		{
			Date next_workday{ year, ++month, (day + days_until_workday) % day_count };	
			return next_workday;
		}
	}
	else
	{
		Date next_workday{ year, month, day + days_until_workday };
		return next_workday;
	}
}

// returns the week number of the year, taking the weekday of Jan 1st into account. Assumes Sunday is the first weekday.
int weekOfYear(const Date& date)
{
	int day_of_year = 0;
	for (Date::Month past_month = Date::Month::jan; past_month < date.getMonth(); ++past_month)	// loop through every month except the current one
		day_of_year += getDayCount(past_month, leapyear(date.getYear()));

	// add days from current month + offset from week day of this year's Jan 1st (sun = 0, [...], sat = 6)
	day_of_year += date.getDay() + getWeekDay(Date{ date.getYear(), Date::Month::jan, 1 });

	return ((int)ceil((double)day_of_year / 7.0));
}

/**************************************************************************************************/
/*											 MAIN        										  */
/**************************************************************************************************/

int main()
{
	try
	{
		Date d{ 2024, Date::Month::feb, 29 };
		cout << "Today's " << d << endl;
		cout << "Week number: " << weekOfYear(d) << endl;

		// construct with days since day 0
		Date d1{ 365 + 31 + 27 + 1 };
		Date d2{ 7869 };
		Date d3{ 730 + 31 + 28 + 1 };
		cout << d1 << endl;
		cout << d2 << endl;
		cout << d3 << endl;
		

		// construct with another Date 
		Date d4{ 2024, Date::Month::feb, 29 };
		Date d5{ 3451, Date::Month::jul, 19 };
		Date d6{ 2003, Date::Month::oct, 10 };
		
		cout << d4.getPassedDays() << endl;
		cout << d5.getPassedDays() << endl;
		cout << d6.getPassedDays() << endl;
		

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

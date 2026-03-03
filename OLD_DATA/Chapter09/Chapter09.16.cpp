// 26/02/2026
// Chapter09.16.cpp
// Exercises

//
// [20] Write the function print_year mentioned in §9.9.2.
//
// Note:
//     To implement this function I had to rebuild large parts of the book's program structure, as explained in §9.9.
//     This means that my code only begins from the 'FUNCTIONS' segment onwards.
//

#include "PPPheaders.h"

/**************************************************************************************************/
/*											CONSTANTS											  */
/**************************************************************************************************/

constexpr int not_a_reading{ -7777 };
constexpr int not_a_month{ -1 };
constexpr int implausible_min{ -200 };
constexpr int implausible_max{ 200 };

/**************************************************************************************************/
/*											STRUCTS												  */
/**************************************************************************************************/

struct Day
{
	vector<double> temp = vector<double>(24, not_a_reading);
};

struct Month							// A month of temperature readings
{
	int month = not_a_month;			// [0:11] January is 0
	vector<Day> day = vector<Day>(31);	// [0:30] one vector of readings per day
};

struct Year										// a year of temperature readings, organized by month
{
	int year = 0;								// positive == A.D.
	vector<Month> month = vector<Month>(12);	// [0:11] January is 0
};

/**************************************************************************************************/
/*											FUNCTIONS											  */
/**************************************************************************************************/

string monthNumToName(const int& month_num)
{
	switch (month_num)
	{
	case 0:
		return "jan";
	case 1:
		return "feb";
	case 2:
		return "mar";
	case 3:
		return "apr";
	case 4:
		return "may";
	case 5:
		return "jun";
	case 6:
		return "jul";
	case 7:
		return "aug";
	case 8:
		return "sep";
	case 9:
		return "oct";
	case 10:
		return "nov";
	case 11:
		return "dec";
	case not_a_month:
		error("invalid month initialization - monthNumToName()");
		return NULL;	// makes compiler shut up
	default:
		error("invalid month_num in monthNumToName()");
		return NULL;	// makes compiler shut up
	}
}

// Generate a randomized day
Day getRandomDay()
{
	Day d;
	for (double& hour : d.temp)
		if (!random_int(19))	// Chance of 1/20 to land on 0
			hour = (double)random_int(implausible_min * 100, implausible_max * 100) / 100.0;	// [-200.00:200.00]
	return d;
}

// Generate a randomized month
Month getRandomMonth(const int& month_num)
{
	Month m;
	m.month = month_num;
	bool day_got = false;

	for (Day& d : m.day)
		if (!random_int(9))		// Chance of 1/10
		{
			d = getRandomDay();
			day_got = true;
		}
	if (!day_got)
		m.day[random_int(30)] = getRandomDay();	// This prevents empty months being generated
	return m;
}

// Generate a randomized year
Year getRandomYear(const int& year_num)
{
	Year y;
	y.year = year_num;
	for (int i = 0; i < y.month.size(); ++i)
		if (!random_int(9))		// Chance of 1/10
			y.month[i] = getRandomMonth(i);
	return y;
}

ostream& printDay(ostream& os, const Day& d, const int& day_num)
{
	for (int hour = 0; hour < d.temp.size(); ++hour)
		if (d.temp[hour] != not_a_reading)
			os << '(' << day_num << ' ' << hour << ' ' << d.temp[hour] << ") ";
	return os;
}

ostream& printMonth(ostream& os, const Month& m)
{
	string month_name{ monthNumToName(m.month) };

	os << "{ month " << month_name << ' ';
	for (int i = 0; i < m.day.size(); ++i)
		printDay(os, m.day[i], i);
	os << '}';
	return os;
}

ostream& print_year(ostream& os, const Year& y)
{
	os << "{ year " << y.year << ' ';
	for (int i = 0; i < y.month.size(); ++i)
		if (y.month[i].month != not_a_month)
			printMonth(os, y.month[i]);
	os << '}' << endl;
	return os;
}

// Generate some years and print them using print_year()
void makeAndPrintYears()
{
	seed((int)time(NULL));
	// Generate and print out 10 years
	for (int i = 0; i < 10; ++i)
	{
		int year_num = 2000 + i;
		Year year = getRandomYear(year_num);
		print_year(cout, year);
	}
}

/**************************************************************************************************/
/*												MAIN											  */
/**************************************************************************************************/

int main()
{
	try
	{
		makeAndPrintYears();
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

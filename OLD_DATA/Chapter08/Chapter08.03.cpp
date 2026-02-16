// 05/02/2026
// Chapter08.03.cpp
// Exercises

//
// [5] Design and implement a Book class. It should have members for ISBN, title, author, and copyright date.
//     Also store data on whether or not the book is checked out. Create functions for returning those data values.
//     Create functions for checking a book in and out.
//     Do simple validation of data entered into a Book; for example, accept ISBNs only of the form n-n-n-x,
//     where n is an integer and x is a digit or a letter. Store an ISBN as a string.
//
// [6] Add operators for the Book class.
//     Have the == and != operators check whether the ISBN numbers are the same for two books.
//     Have a << print out the title, author, and ISBN on separate lines.
//
// [7] Create an enum type for the Book class called Genre.
//     Give each book a Genre and make appropriate changes to the Book constructor and member functions.
//
// [8] Create a Patron class. The class will have a user's name, library card number, and library fees (if owed).
//     Have functions that access this data, as well as a function to set the fee of the user.
//     Have a helper function that returns a Boolean depending on whether or not the user owes a fee.
//
// [9] Create Library Class. Include vectors of Books and Patrons.
//     Include a struct called Transaction to record when a Book is checked out. Have it include a Book, a Patron and a Date.
//     Make a vector of transactions to keep a record of which Books are out.
//     Create functions to add Books to the library, add Patrons to the library and check out books.
//     Whenever a Patron checks out a Book, have the library make sure that both the Patron and the Book are in the library.
//     If they aren't, report an error.
//     Then check to make sure that the Patron owes no fees. If they do, report an error.
//     If not, create a Transaction, and place it in the vector of Transactions.
//     Also write a function that will return a vector that contains the names of all Patrons who owe fees.
//
// [10] Implement leapyear(int).
// 
// [11] Design and implement a set of useful helper functions for the Date class with functions such as nextWorkday() and weekOfYear().
//      Assume that any day that is not Saturday or Sunday is a workday.
//      Assume that week 1 is the week with January 1 in it and that the first day of the week is Sunday.
//

#include "PPPheaders.h"

/**************************************************************************************************/
/*										CLASS DEFINITIONS										  */
/**************************************************************************************************/

/**************** Library ****************/
/*****************************************/

class Library
{
public:
	/**************** Book ****************/
	/**************************************/

	class Book
	{
	public:
		enum class Genre
		{
			fiction, nonfiction, periodical, biography, children, other
		};

		Book() :genre{ Genre::nonfiction }, title { "Programming: Principles and Practice Using C++" }, author{ "Bjarne Stroustrup" }, isbn_num{ "0-13-830868-3" },
			copyright_date{ 2024 } {}
		Book(const Genre& book_genre, const string& book_title, const string& book_author, const string& book_isbn, const int& book_copyright_date)
			:genre{ book_genre }, title{ book_title }, author{ book_author }, isbn_num{ book_isbn }, copyright_date{ book_copyright_date }
		{
			if (isValidBook())
				return;
			else
				error("invalid Book construction");
		}

		// validate objects
		bool isValidBook() { return (isValidISBN() /* add more validation functions later? */ ); }

		// return member values
		const string& getTitle() const { return title; }
		const Genre& getGenre() const { return genre; }
		const string& getAuthor() const { return author; }
		const string& getISBN() const { return isbn_num; }
		const int& getCopyrightDate() const { return copyright_date; }
		const bool& isCheckedOut() const { return is_checked_out; }

		// change member values
		void checkIn()
		{
			if (!is_checked_out) { error("Book not checked out"); }
			else { is_checked_out = false; }
		}
		void checkOut()
		{
			if (is_checked_out) { error("Book already checked out"); }
			else { is_checked_out = true; }
		}

	private:
		// only called by isValidBook()
		bool isValidISBN();

		Genre genre;
		string title, author, isbn_num;		// using ISBN-10, because it fits the n-n-n-x format (unlike ISBN-13)
		int copyright_date;
		bool is_checked_out = false;
	};

	/**************** Patron ****************/
	/****************************************/

	class Patron 
	{
	public:
		Patron() :name{ "Max Mustermann" }, card_num{ 123456 }, owed_fees{ 0.0 } {}
		Patron(const string& patron_name, const int& patron_card_num, const double& patron_owed_fees = 0.0) :name{ patron_name }, card_num{ patron_card_num }, owed_fees{ patron_owed_fees }
		{
			if (isValidPatron())
				return;
			else
				error("invalid Patron construction");
		}

		// validate objects
		bool isValidPatron() const { return (isValidCardNum() && isValidOwedFees()); }

		// return member values
		const string& getName() const { return name; }
		const int& getCardNum() const { return card_num; }
		const double& getOwedFees() const { return owed_fees; }

		// change member values
		void setOwedFees(const double& new_patron_owed_fees) { owed_fees = new_patron_owed_fees; }	// does this create a temporary object to reference if a literal is passed? const references are weird.
		void clearOwedFees() { owed_fees = 0.0; }

	private:
		// only called by isValidPatron()
		bool isValidCardNum() const;
		bool isValidOwedFees() const;

		string name;
		int card_num;		// six-digit num
		double owed_fees;
	};

	/**************** Date ****************/
	/**************************************/

	class Date
	{
	public:
		// Year and Day serve no real purpose, they just improve readability
		struct Year
		{
			Year() :y{ 2020 } {}
			Year(int yy) :y{ yy } {}

			int y;
		};

		enum class Month
		{
			jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
		};

		struct Day
		{
			Day() :d{ 2 } {}
			Day(int dd) :d{ dd } {}

			int d;
		};

		Date() :y{ 2020 }, m{ 2 }, d{ 2 } {}
		Date(Year yy, Month mm, Day dd) :y{ yy }, m{ mm }, d{ dd }
		{	
			if (isValidDate(yy, mm, dd))
				return;
			else
				error("invalid Date");
		}

		// validate
		bool isValidDate(Year yy, Month mm, Day dd) const { return isValidMonth(mm) && isValidDay(leapyear(yy), mm, dd); }
		bool leapyear(const Year& yy) const { return ((yy.y % 4 == 0 && yy.y % 100 != 0) || yy.y % 400 == 0); }				// return true if year is divisible by 4 and not 100, or if it is divisible by 400

		// return member values
		int getYear() const { return y.y; }
		Month getMonth() const { return m; }
		int getDay() const { return d.d; }

	private:
		// only called by isValidDate()
		bool isValidMonth(const Month& mm) const { return (Month::jan <= mm && mm <= Month::dec); }
		bool isValidDay(const bool&, const Month&, const Day&) const;

		Year y;
		Month m;
		Day d;
	};

	/**************** Transaction ****************/
	/*********************************************/

	struct Transaction
	{
		Transaction(const Book& book, const Patron& patron, const Date& date) :transact_book{ book }, transact_patron{ patron }, transact_date{ date } {}

		Book transact_book;
		Patron transact_patron;
		Date transact_date;
	};

	/**************** Member Functions ****************/
	/**************************************************/

	Library() {}

	// return member values
	const vector<Patron> getDebtors() const;

	// print member values
	const vector<Transaction>& getTransactions() const { return transact_vec; }

	// change member values
	void addBook(Book& new_book) { book_vec.push_back(new_book); }
	void addPatron(Patron& new_patron) { patron_vec.push_back(new_patron); }
	void checkOutBook(Book&, const Patron&, const Date&);

private:
	vector<Book> book_vec;
	vector<Patron> patron_vec;
	vector<Transaction> transact_vec;
};

/**************** Necessary forward-declarations ****************/
/****************************************************************/

// Book comparison (by ISBN)
bool operator==(const Library::Book&, const Library::Book&);

// Patron comparioson (by card_num)
bool operator==(const Library::Patron&, const Library::Patron&);

/**************** Book outside-class definitions ****************/
/****************************************************************/

// checks ISBN format using stringstream
// does NOT check n digit count yet
bool Library::Book::isValidISBN()
{
	// correct format: n-n-n-x		(n = int, x = int or a letter)
	stringstream ss;
	ss.str(isbn_num);	// put ISBN into sstream
	string line;
	int i = 0;

	// this loop handles n-n-n-, leaving only x
	for (; i < 3 && getline(ss, line, '-'); i++)	// gets each instance of n- out of ss and puts it into line ('-' discarded)
	{
		if (line.empty())
			return false;

		for (char ch : line)
			if (!isdigit(ch))
				return false;
	}
	// this handles x (last "loop")
	getline(ss, line);

	// checks if the correct amount of loops was performed (3 out of 4),
	// that there is only one symbol left (x),
	// and that x is valid
	if (i == 3 && line.length() == 1 && (isdigit(line[0]) || isalpha(line[0])))
		return true;
	else
		return false;
}

/**************** Patron outside-class definitions ****************/
/******************************************************************/

// checks that card_num is positive and has 6 digits
bool Library::Patron::isValidCardNum() const
{
	if (card_num <= 0) { return false; }

	if (((int)log10((double)card_num) + 1) == 6)
		return true;
	else
		return false;
}

// checks that owed_fees is positive
bool Library::Patron::isValidOwedFees() const
{
	if (owed_fees < 0) 
		return false;
	else
		return true;
}

/**************** Date outside-class definitions ****************/
/****************************************************************/

// takes leap years and month into account to determine whether a day is valid
bool Library::Date::isValidDay(const bool& is_leap_year, const Library::Date::Month& mm, const Library::Date::Day& dd) const
{
	switch (mm)
	{
	// 31 day months
	case Library::Date::Month::jan: case Library::Date::Month::mar: case Library::Date::Month::may:
	case Library::Date::Month::jul: case Library::Date::Month::aug: case Library::Date::Month::oct: case Library::Date::Month::dec:
		if (dd.d >= 1 && dd.d <= 31)
			return true;
		break;
	// 30 day months
	case Library::Date::Month::apr: case Library::Date::Month::jun: case Library::Date::Month::sep: case Library::Date::Month::nov:
		if (dd.d >= 1 && dd.d <= 30)
			return true;
		break;
	// February
	case Library::Date::Month::feb:
		if (is_leap_year && (dd.d >= 1 && dd.d <= 29))
			return true;
		else if (dd.d >= 1 && dd.d <= 28)
			return true;
		break;

	default:
		error("isValidDay()");	// month was pre-checked, so this shouldn't be possible
	}
	error("invalid Day");
	return NULL;	// will never return, makes compiler shut up though
}

/**************** Library outside-class definitions ****************/
/*******************************************************************/

// returns vector of Patrons that still owe fees
const vector<Library::Patron> Library::getDebtors() const
{
	if (!patron_vec.size()) { error("empty Patron list"); }

	vector<Library::Patron> debtors;
	for (Library::Patron x : patron_vec)
	{
		if (x.getOwedFees())
			debtors.push_back(x);
	}
	return debtors;
}

// checks Book out after performing some checks and adds Transaction to vector
void Library::checkOutBook(Book& new_book,const Patron& new_patron,const Date& new_date)
{
	if (new_patron.getOwedFees())
		error("this Patron still owes fees: ", new_patron.getName());

	int book_vec_size = (int)book_vec.size(), patron_vec_size = (int)patron_vec.size();
	if (!book_vec_size || !patron_vec_size)
		error("empty Book or Patron list");

	int size = (book_vec_size >= patron_vec_size) ? (book_vec_size) : (patron_vec_size);	// always loop with the larger vector size

	// loop through once to look for Book and Patron
	bool book_found = false, patron_found = false;
	for (int i = 0; i < size; i++)
	{
		if (i < book_vec_size && new_book == book_vec[i])			// i < book_vec_size prevents vector range error
		{
			if (book_vec[i].isCheckedOut())
				error("Book already checked out: ", book_vec[i].getTitle());

			book_found = true;
		}
		if (i < patron_vec_size && new_patron == patron_vec[i])		// i < patron_vec_size prevents vector range error
			patron_found = true;
	
		if (book_found && patron_found)
		{
			new_book.checkOut();
			transact_vec.push_back(Transaction(new_book, new_patron, new_date));	// constructs Transaction object only after conditions were met
			return;
		}
	}
	error("invalid transaction: ", new_book.getTitle());
}

/**************************************************************************************************/
/*									  OPERATOR OVERLOADING  									  */
/**************************************************************************************************/

/**************** Book class ****************/
/********************************************/

// Book comparison (by ISBN)
bool operator==(const Library::Book& book_1, const Library::Book& book_2)
{
	return (book_1.getISBN() == book_2.getISBN());
}
bool operator!=(const Library::Book& book_1, const Library::Book& book_2)
{
	return (book_1.getISBN() != book_2.getISBN());
}

// print Genre
ostream& operator<<(ostream& os, Library::Book::Genre genre)	// this is rough, but doing this any better way would be more trouble than it's worth
{
	switch (genre)
	{
	case Library::Book::Genre::fiction:
		return os << "Fiction";

	case Library::Book::Genre::nonfiction:
		return os << "Nonfiction";

	case Library::Book::Genre::periodical:
		return os << "Periodical";

	case Library::Book::Genre::biography:
		return os << "Biography";

	case Library::Book::Genre::children:
		return os << "Children";

	case Library::Book::Genre::other:
		return os << "Other";

	default:
		error("invalid Genre output");
		return os;	// will never return, makes compiler shut up though
	}
}

// print Book data
ostream& operator<<(ostream& os, const Library::Book& book)
{
	os << "***  Book Data  ***\n" << endl;
	os << "Title: " << book.getTitle() << endl;
	os << "Author: " << book.getAuthor() << endl;
	os << "Genre: " << book.getGenre() << endl;
	os << "Copyright date: " << book.getCopyrightDate() << endl;
	os << "ISBN-10: " << book.getISBN() << '\n' << endl;
	os << "It's currently " << ((book.isCheckedOut()) ? ("") : ("not ")) << "checked out." << endl;

	return os;
}

/**************** Patron class ****************/
/**********************************************/

// Patron comparioson (by card_num)
bool operator==(const Library::Patron& patron_1, const Library::Patron& patron_2)
{
	return (patron_1.getCardNum() == patron_2.getCardNum());
}
bool operator!=(const Library::Patron& patron_1, const Library::Patron& patron_2)
{
	return (patron_1.getCardNum() != patron_2.getCardNum());
}

// print Patron data
ostream& operator<<(ostream& os, const Library::Patron& patron)
{
	os << "***  Patron Data  ***\n" << endl;
	os << "Name: " << patron.getName() << endl;
	os << "Library Card Number: " << patron.getCardNum() << endl;
	os << "Owed fees: " << patron.getOwedFees() << endl;

	return os;
}

/**************** Date class ****************/
/********************************************/

// print Date data
ostream& operator<<(ostream& os, const Library::Date& date)
{
	os << "Date: " << date.getDay() << '/' << static_cast<int>(date.getMonth()) << '/' << date.getYear() << endl;

	return os;
}

// adds ++m
Library::Date::Month operator++(Library::Date::Month& M)
{
	M = (M == Library::Date::Month::dec) ? (Library::Date::Month::jan) : (Library::Date::Month{ static_cast<int>(M) + 1 });
	return M;
}

// adds d + int
Library::Date::Day operator+(Library::Date::Day& D, int i) { return (D.d += i); }

// adds d % int
Library::Date::Day operator%(Library::Date::Day& D, int i) { return (D.d %= i); }

/**************************************************************************************************/
/*									  HELPER FUNCTIONS/OTHER  									  */
/**************************************************************************************************/

/**************** Date class ****************/
/********************************************/

// returns the weekday (0-6 with Sunday = 0) using Gauss's algorithm (Gregorian calendar)
int getWeekDay(const Library::Date& date)
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
	case 3: case 11:						// some months share offset values
		m = (date.leapyear(A) ? 4 : 3);		// differing offset value for leap years
		break;
	case 4: case 7:
		m = (date.leapyear(A) ? 0 : 6);
		break;
	case 5:
		m = (date.leapyear(A) ? 2 : 1);
		break;
	case 6:
		m = (date.leapyear(A) ? 5 : 4);
		break;
	case 8:
		m = (date.leapyear(A) ? 3 : 2);
		break;
	case 9: case 12:
		m = (date.leapyear(A) ? 6 : 5);
		break;
	case 10:
		m = (date.leapyear(A) ? 1 : 0);
		break;
	default:
		error("getWeekday()");
	}

	int week_day = (D + m + 5 * ((A - 1) % 4) + 4 * ((A - 1) % 100) + 6 * ((A - 1) % 400)) % 7;
	return week_day;
}

// returns the Date of the next day that isn't a Saturday or Sunday
Library::Date nextWorkday(const Library::Date& date)
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
	Library::Date::Month month = date.getMonth();
	int day = date.getDay();

	// calculate next workday date
	switch (static_cast<int>(month))
	{
	// 31 day months
	case 1: case 3: case 5:
	case 7: case 8: case 10:
		if ((day + days_until_workday) > 31)	// increment month
		{
			Library::Date next_workday{ year, ++month, (day + days_until_workday) % 31};	// using % works because sum must be > 31, returning 1-3
			return next_workday;
		}
		else
		{
			Library::Date next_workday{ year, month, day + days_until_workday};
			return next_workday;
		}
	// 30 day months
	case 4: case 6: case 9: case 11:
		if ((day + days_until_workday) > 30)
		{
			Library::Date next_workday{ year, ++month, (day + days_until_workday) % 30 };
			return next_workday;
		}
		else
		{
			Library::Date next_workday{ year, month, day + days_until_workday };
			return next_workday;
		}
	// February
	case 2:
		if (date.leapyear(year) && (day + days_until_workday) > 29)
		{
			Library::Date next_workday{ year, ++month, (day + days_until_workday) % 29 };
			return next_workday;
		}
		else if ((day + days_until_workday) > 28)
		{
			Library::Date next_workday{ year, ++month, (day + days_until_workday) % 28 };
			return next_workday;
		}
		else
		{
			Library::Date next_workday{ year, month, day + days_until_workday };
			return next_workday;
		}
	// December
	case 12:
		if ((day + days_until_workday) > 31)	// increment year (and month)
		{
			Library::Date next_workday{ ++year, ++month, (day + days_until_workday) % 31 };
			return next_workday;
		}
		else
		{
			Library::Date next_workday{ year, month, day + days_until_workday };
			return next_workday;
		}
	default:
		error("nextWorkday()");
	}
	return date; // will never return, makes compiler shut up though
}

// returns the week number of the year, taking the weekday of Jan 1st into account. Assumes Sunday is the first weekday.
int weekOfYear(const Library::Date& date)
{
	int day_of_year = 0;
	for (int i = 1; i < static_cast<int>(date.getMonth()); i++)	// loop through every month except the current one
	{
		switch (i)
		{
		case 1: case 3: case 5:
		case 7: case 8: case 10: case 12:
			day_of_year += 31;
			break;

		case 4: case 6: case 9: case 11:
			day_of_year += 30;
			break;

		case 2:
			if (date.leapyear(date.getYear()))
				day_of_year += 29;
			else
				day_of_year += 28;
			break;

		default:
			error("weekOfYear()");	// month was pre-checked, so this shouldn't be possible
		}
	}
	// add days from current month + offset from week day of this year's Jan 1st (sun = 0, [...], sat = 6)
	day_of_year += date.getDay() + getWeekDay(Library::Date{date.getYear(), Library::Date::Month::jan, 1});

	return ((int)ceil((double)day_of_year / 7.0));
}	

/**************************************************************************************************/
/*											TESTING        										  */
/**************************************************************************************************/

void testLibrary()
{
	Library lib;

	Library::Book b1{};
	Library::Book b2{ Library::Book::Genre::children, "Second Book", "Me", "0-1324-123-Z", 2026 };

	Library::Patron p1;
	Library::Patron p2{ "Harry DuBois", 696941, 131.25 };
	Library::Patron p3{ "Kim Kitsuragi", 314159};
	Library::Patron p4{ "Titus Hardie", 100000, 47.87};
	Library::Patron p5{ "Evrart Claire", 999887, 1.24};

	lib.addBook(b1);
	lib.addBook(b2);

	lib.addPatron(p1);
	lib.addPatron(p2);
	lib.addPatron(p3);
	lib.addPatron(p4);
	lib.addPatron(p5);

	lib.checkOutBook(b1, p1, Library::Date{});
	lib.checkOutBook(b2, p3, Library::Date{ 2028, Library::Date::Month::feb, 29 });		// leap year

	vector<Library::Transaction> ref = lib.getTransactions();
	for (int i = 0; i < ref.size(); i++)
	{
		cout << "****  Transaction #" << i + 1 << " ****" << endl;
		cout << ref[i].transact_book << endl;
		cout << ref[i].transact_patron << endl;
		cout << ref[i].transact_date << endl;
	}
}

void testBook()
{
	Library::Book b1;
	Library::Book b2{ Library::Book::Genre::children, "Second Book", "Me", "0-1324-123-Z", 2026 };

	cout << b1 << endl;
	cout << b2 << '\n' << endl;

	if (b1 == b2)
		cout << "Equal!" << endl;
	else if (b1 != b2)
		cout << "Not equal!" << endl;
}

void testPatron()
{
	Library::Patron p1;
	Library::Patron p2{ "Harry DuBois", 696941, 131.25 };

	cout << p1.getName() << endl;
	cout << p2.getName()<< endl;
	
	cout << p1.getCardNum() << endl;
	cout << p2.getCardNum()<< endl;
	
	cout << p1.getOwedFees() << endl;
	cout << p2.getOwedFees()<< endl;
	
	cout << ((p1.getOwedFees() != 0) ? "True" : "False") << endl;
	cout << ((p2.getOwedFees() != 0) ? "True" : "False") << endl;
	
	p1.setOwedFees(3.14);
	p2.clearOwedFees();
	
	cout << p1.getOwedFees() << endl;
	cout << p2.getOwedFees()<< endl;
	
	cout << ((p1.getOwedFees() != 0) ? "True" : "False") << endl;
	cout << ((p2.getOwedFees() != 0) ? "True" : "False") << endl;
}

/**************************************************************************************************/
/*											 MAIN        										  */
/**************************************************************************************************/

int main()
{
	try
	{
		testLibrary();
		
		/* Test Date helper functions
		Library::Date d{ 2024, Library::Date::Month::feb, 29 };

		cout << d << endl;
		cout << nextWorkday(d) << endl;
		cout << "Success!" << endl;
		*/

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

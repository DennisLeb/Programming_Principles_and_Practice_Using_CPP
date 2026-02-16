// 04/02/2026
// Chapter08.02.cpp
// Exercises

//
// [2] Design and implement a Name_pairs class holding (name, age) pairs. Represent that as a vector<string> name and a vector<double> age member.
//     Provide an input operation readNames() and a readAges() operation that prompts the user for an age for each name.
//     Provide a print() operation that outputs the (name[i], age[i]) pairs in the order determined by the name vector.
//     Provide a sort() operation that sorts the name vector in alphabetical order and reorganized the age vector to match.
//     Implement all "operations" as member functions.
//
// [3] Replace Name_pairs::print() with a (global) operator << and define == and != for Name_pairs.
//
// [4] Do the previous exercise but implement Name_pairs using a Name_pair class.
//

#include "PPPheaders.h"
#define QUITKEY "done"

/**************************************************************************************************/
/*										CLASS DEFINITION										  */
/**************************************************************************************************/

// provides vector of string and double pairs
class Name_pairs {
public:
	// provides one object for a pair of string and double
	class Name_pair {
	public:
		Name_pair(string s) :name{ s }, age{ 0 } {}	// is always constructed like this
		void assignAge(const double& d) 
		{
			if (d < 0 || d > 122)		// 122 is the oldest a human ever got
				error("invalid age");
			age = d;
			return; 
		}
		
		// access private members
		const string& getName() const { return name; }
		const double& getAge() const { return age; }

	private:
		string name;
		double age;
	};

	Name_pairs() :vec_size{0} {}	// no default values needed for vector
	void readNames();
	void readAges();
	void sort();
	bool hasDuplicateName() const;
	
	// access private members
	const vector<Name_pair>& getPairsVec() const { return pairs; }
	const int& getVecSize() const { return vec_size; }

private:
	vector<Name_pair> pairs;
	int vec_size;
};

// outside class function definitions
void Name_pairs::readNames()
{
	if (!(pairs.empty()))
		error("non-empty vector passed to readNames()");

	string new_name;
	cout << "Enter some names (type \"" << QUITKEY << "\" when done) > ";
	while (true) {
		cin >> new_name;
		if (cin.fail())
			error("invalid input");
		if (new_name == QUITKEY)
			break;
		pairs.push_back(Name_pair(new_name));
	}
	cout << endl;

	vec_size = int(pairs.size());

	if (vec_size == 0)
		error("no names entered");
	if (hasDuplicateName())
		error("duplicate name");

	return;
}

void Name_pairs::readAges()
{
	double new_age;
	cout << "Enter one age per name.\n" << endl;
	for (int i = 0; i < vec_size; i++) {
		cout << "How old is " << pairs[i].getName() << "? > ";
		cin >> new_age;
		if (cin.fail())
			error("invalid input");
		pairs[i].assignAge(new_age);
	}
	cout << endl;
	return;
}

void Name_pairs::sort()
{
	ranges::sort(pairs.begin(), pairs.end(), [](const Name_pair& pair_1, const Name_pair& pair_2)
		{
			// enables sorting Name_pair by comparing name values
			return (pair_1.getName() < pair_2.getName());
		});

	return;
}

bool Name_pairs::hasDuplicateName() const
{
	// checks for identical names
	for (int i = 0; i < vec_size; i++) {
		for (int j = 0; j < vec_size; j++) {
			if (i == j)
				continue;
			if (pairs[i].getName() == pairs[j].getName())
				return true;
		}
	}
	return false;
}

/**************************************************************************************************/
/*									  OPERATOR OVERLOADING  									  */
/**************************************************************************************************/

// Name_pair
// necessary to compare vector<Name_pair>
bool operator==(const Name_pairs::Name_pair& pair_1, const Name_pairs::Name_pair& pair_2)
{
	return (pair_1.getName() == pair_2.getName() && pair_1.getAge() == pair_2.getAge());
}

// Name_pairs
// outputting Name_pairs
ostream& operator<<(ostream& os, const Name_pairs& pairs)
{
	for (int i = 0; i < pairs.getVecSize(); i++)
		os << "Pair #" << i + 1 << ": " << pairs.getPairsVec()[i].getName() << ", " << pairs.getPairsVec()[i].getAge() << endl;
	return os;
}

// compares vector<Name_pair>
bool operator==(const Name_pairs& pairs_1, const Name_pairs& pairs_2)
{
	return (pairs_1.getPairsVec() == pairs_2.getPairsVec());
}
bool operator!=(const Name_pairs& pairs_1, const Name_pairs& pairs_2)
{
	return (pairs_1.getPairsVec() != pairs_2.getPairsVec());
}

/**************************************************************************************************/
/*											 MAIN        										  */
/**************************************************************************************************/

int main()
{
	try {
		/* Testing operator overloading (==, !=)
		Name_pairs pairs;
		pairs.readNames();
		pairs.readAges();

		Name_pairs pairs_2;
		pairs_2.readNames();
		pairs_2.readAges();

		if (pairs == pairs_2)
			cout << "Great Success!" << endl;
		else if (pairs != pairs_2)
			cout << "Epic Fail!" << endl;
		*/
		
		Name_pairs pairs;
		pairs.readNames();
		pairs.readAges();
		
		cout << "Printing unsorted list...\n" << endl;
		cout << pairs << endl;

		cout << "Sorting names...\n" << endl;
		pairs.sort();

		cout << "Printing sorted list...\n" << endl;
		cout << pairs;
		
		return 0;
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown error: " << endl;
		return 2;
	}
}

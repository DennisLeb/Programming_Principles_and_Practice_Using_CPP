// 25/02/2026
// Chapter09.15.cpp (store_temps.cpp; temp_stats.cpp)
// Exercises

//
// [17] Write a program that creates a file of data in the form of the temperature 'Reading' type defined in §9.3.2.
//		For testing, fill the file with at least 50 "temperature readings".
//		Call this program 'store_temps.cpp' and the file it creates 'raw_temps.txt' (not doing this for file readability reasons).
//
// [18] Write a program that reads the data from 'raw_temps.txt' into a vector and then calculates the mean and median temperatures in your data set.
//		Call this program 'temp_stats.cpp'.
//
// [19] Modify the 'store_temps.cpp' program to include a temperature suffix c for Celsius or f for Fahrenheit temperatures.
//		Then modify the 'temp_stats.cpp' program to test each temperature, converting the Celsius to Fahrenheit before putting them into the vector.
//

#include "PPPheaders.h"

/**************************************************************************************************/
/*											CONSTANTS											  */
/**************************************************************************************************/

constexpr char celsius_symbol{ 'c' };
constexpr char fahrenheit_symbol{ 'f' };

/**************************************************************************************************/
/*										STRUCT DEFINITION										  */
/**************************************************************************************************/

struct Reading
{
	enum class Temp_unit
	{
		celsius, fahrenheit
	};

	Reading() :hour{ 0 }, temperature{ 0.0 }, unit{ Temp_unit::celsius } {}
	Reading(const int& hour_val, const double& temp_val, const Temp_unit& unit_val = Temp_unit::celsius) :hour{hour_val}, temperature{temp_val}, unit{unit_val} {}

	int hour;			// [0:23]
	double temperature;
	Temp_unit unit;
};

/**************************************************************************************************/
/*										FUNCTION DEFINITIONS									  */
/**************************************************************************************************/

void store_temps(const string& file_name)
{
	ofstream ofs{ file_name };	// this would be raw_temps.txt
	if (!ofs)
		error("unable to open output file");

	vector<Reading> temps;

	// Get 50 randomized test values.
	seed((int)time(NULL));
	for (int i = 0; i < 50; ++i)
	{
		Reading new_reading;
		new_reading.hour = random_int(23);										// [0:23]
		new_reading.unit = Reading::Temp_unit{ random_int(1) };					// [0:1] (0 = celsius, 1 = fahrenheit)
		new_reading.temperature = (new_reading.unit == Reading::Temp_unit::celsius ? (double)random_int(-27315, 99999) / 100.0 : (double)random_int(-45967, 99999) / 100.0);	// [-273.15:999.99] or [-459.67:999.99] (this maximum is arbitrary)
		temps.push_back(new_reading);
	}

	for (Reading& r : temps)
		ofs << '(' << r.hour << ", " << setprecision(8) << r.temperature << (r.unit == Reading::Temp_unit::celsius ? celsius_symbol : fahrenheit_symbol) << ')' << endl;
	ofs.close();

	cout << "Done storing temps!" << endl;
	return;
}

vector<Reading> read_temps(const string& file_name)
{
	ifstream ifs{ file_name };
	if (!ifs)
		error("unable to open input file");

	char left_paren = '\0', comma = '\0', unit = '\0', right_paren = '\0';
	int hour = 0;
	double temp = 0.0;
	vector<Reading> temps;
	while (ifs >> left_paren >> hour >> comma >> setprecision(8) >> temp >> unit >> right_paren)
	{
		if (left_paren != '(' || comma != ',' || right_paren != ')' || (unit != celsius_symbol && unit != fahrenheit_symbol))
		{
			ifs.clear(ios::failbit);
			break;
		}
		if (unit == fahrenheit_symbol)
			temp = (temp - 32) / 1.8;

		temps.push_back(Reading{ hour, temp, Reading::Temp_unit::celsius});
	}
	if (!ifs && !ifs.eof() || temps.empty())
		error("invalid input file format");
	ifs.close();
	
	cout << "Done reading temps!" << endl;
	return temps;
}

double calculate_mean(const vector<Reading>& temps)
{
	double sum = 0.0;
	for (const Reading& r : temps)
		sum += r.temperature;
	
	cout << "Done calculating mean!" << endl;
	return (sum / temps.size());
}

double calculate_median(const vector<Reading>& temps)
{
	vector<double> sorted_temps;
	for (const Reading& temp : temps)
		sorted_temps.push_back(temp.temperature);	// I did sort of cheat by extracting the temperature separately and not making a sort() for the Reading type.

	ranges::sort(sorted_temps);

	double median = 0.0;
	if (sorted_temps.size() % 2 == 0)	// is it even? (median != element of temps)
		median = (sorted_temps[sorted_temps.size() / 2] + sorted_temps[(sorted_temps.size() / 2) - 1]) / 2;	// gets average of the two middling values

	else								// otherwise it's odd (median == element of temps)
		median = sorted_temps[sorted_temps.size() / 2];

	cout << "Done calculating median!" << endl;
	return median;
}

void print_results(const vector<Reading>& temps, const double& mean, const double& median)
{
	cout << "\nTemps:" << endl;
	for (const Reading& r : temps)
		cout << '(' << r.hour << ", " << setprecision(8) << r.temperature << (r.unit == Reading::Temp_unit::celsius ? celsius_symbol : fahrenheit_symbol) << ')' << endl;

	cout << "\nMean value in " << celsius_symbol << ": " << mean << endl;
	cout << "Median value in " << celsius_symbol << ": " << median << endl;
	cout << "\nDone printing results!" << endl;
	return;
}

/**************************************************************************************************/
/*												MAIN											  */
/**************************************************************************************************/

int main()
{
	try
	{
		const string file_name{ "Chapter09.15.1.txt" };

		// Construct 50 test values and write to file (put into comment to not generate new file each time)
		store_temps(file_name);

		// Read those values from file
		vector<Reading> temps{ read_temps(file_name) };

		double mean_of_temps{ calculate_mean(temps) };
		double median_of_temps{ calculate_median(temps) };

		print_results(temps, mean_of_temps, median_of_temps);
		
		cout << "\nDone!" << endl;
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

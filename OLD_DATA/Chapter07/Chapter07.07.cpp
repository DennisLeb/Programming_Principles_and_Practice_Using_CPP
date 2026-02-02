// 02/02/2026
// Chapter07.07.cpp
// Exercises

//
// [9] Write a function that given two vector<double>s price and weight computes a value (an "index") that is the sum of all price[i] * weight[i].
//     Make sure to have prize.size() == weight.size().
//
// [10] Write a function maxv() that returns the largest element of a vector argument.
// 
// [11] Write a function that finds the smallest and the largest element of a vector argument and also computes the mean and the median.
//      Either return a struct containing several result values or pass them back through reference arguments.
//      Which do you prefer and why?
//      Median:
//          A number so that exactly as many elements come before it in the sequence, as come after it. Does not need to be an element of the sequence.
//
//      Ans:
//          I find using a struct with a constructor function to find all values upon initialization much more convenient than many disorganized references.
//          That being said, my struct does also work with const-references, so I'm kind of using the best of both worlds.
//

#include "PPPheaders.h"

// excluded from vec_properties, because it uses two vector<double> arguments
double getIndex(const vector<double>& vec1, const vector<double>& vec2) {

	if (vec1.size() != vec2.size())
		error("vectors of differing sizes passed to getIndex()");

	if (vec1.size() == 0)
		error("empty vectors passed to getIndex()");

	double local_index = 0;
	for (int i = 0; i < vec1.size(); i++)
		local_index += vec1[i] * vec2[i];
	
	return local_index;
}

struct vec_properties {
	vec_properties(const vector<double>& vec) :largest(maxv(vec)), smallest(minv(vec)), mean(getMean(vec)), median(getMedian(vec)) {};

	double largest = 0;
	double smallest = 0;
	double mean = 0;
	double median = 0;

private:
	double maxv(const vector<double>&);
	double minv(const vector<double>&);
	double getMean(const vector<double>&);
	double getMedian(const vector<double>&);
};

double vec_properties::maxv(const vector<double>& vec) {

	if (vec.size() == 0)
		error("empty vector passed to maxv()");

	double local_largest = 0;
	for (double x : vec)
		if (x > local_largest)
			local_largest = x;
	
	return local_largest;
}

double vec_properties::minv(const vector<double>& vec) {

	if (vec.size() == 0)
		error("empty vector passed to minv()");
	
	double local_smallest = vec[0];
	for (double x : vec)
		if (x < local_smallest)
			local_smallest = x;
	
	return local_smallest;
}

double vec_properties::getMean(const vector<double>& vec) {

	if (vec.size() == 0)
		error("empty vector passed to getMean()");

	double local_mean = 0;
	for (double x : vec)
		local_mean += x;

	return (local_mean / vec.size());
}

double vec_properties::getMedian(const vector<double>& vec) {

	if (vec.size() == 0)
		error("empty vector passed to getMedian()");

	double local_median = 0;
	vector<double> sorted_vec = vec;	// this copy bugs me but I can't find a good way around it right now
	ranges::sort(sorted_vec);

	if (sorted_vec.size() % 2 == 0)	// is it even? (median != element of vec)
		local_median = (sorted_vec[sorted_vec.size() / 2] + sorted_vec[(sorted_vec.size() / 2) - 1]) / 2;	// gets average of the two middling values
	
	else							// otherwise it's odd (median == element of vec)
		local_median = sorted_vec[sorted_vec.size() / 2];
	
	return local_median;
}

int main() {

	try {
		vector<double> price{ 3.99, 7.45, 45.95, 2.15, 4.99, 17.35, 9.99, 24.75, 6.95, 16.10, .99, 5.00, 65.15 };
		vector<double> weight{ 4.67, 11.13, 6.23, 19.42, 37.31, 9.87, 2.68, .75, 10.64, 6.29, 21.14, 14.35, 39.44 };	// price.size() == weight.size() == 13

		// get properties using constructor
		vec_properties price_prop(price);
		vec_properties weight_prop(weight);

		double index = getIndex(price, weight);
		cout << "Your index amounts to: " << index << '.' << endl << endl;

		cout << "Most expensive item: " << price_prop.largest << "$." << endl;
		cout << "Heaviest item: " << weight_prop.largest << "lb." << endl << endl;

		cout << "Least expensive item: " << price_prop.smallest << "$." << endl;
		cout << "Lightest item: " << weight_prop.smallest<< "lb." << endl << endl;

		cout << "Mean of prices: " << price_prop.mean<< "$." << endl;
		cout << "Mean of weights: " << weight_prop.mean<< "lb." << endl << endl;

		cout << "Median price: " << price_prop.median<< "$." << endl;
		cout << "Median weight: " << weight_prop.median<< "lb." << endl;
		return 0;
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << endl;
		return 1;
	}
	catch (...) {
		cerr << "unknown error";
		return 2;
	}
}

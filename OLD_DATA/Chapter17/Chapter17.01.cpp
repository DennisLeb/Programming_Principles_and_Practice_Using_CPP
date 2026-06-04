// 02/06/2026
// Chapter17.01.cpp
// Exercises

//
// [1] Define a class 'Matrix' to represent a two-dimensional matrix of 'double's.
//     A constructor should take two integer arguments specifying the number of rows and columns, e.g., 'Matrix{ 3, 4 }' has 3 rows and 4 columns.
//     Provide 'Matrix' with operators '=' (assignment), '==' (equality), '[]' (subscript), and '+' (addition of corresponding elements).
//     The subscript operator should take a pair of indices, e.g., 'm[2,3]' yields the element 3 of the 2nd row.
//     Indexing should be zero-based.
//     Range check your indices.
//     Reject operations on two 'Matrix's with different dimensions.
//     If your compiler doesn't allow multiple arguments for '[]', use '()' instead.
//     Store the elements of your 'Matrix' in a single 'vector'.
//     Test 'Matrix'.
//
// [2] Provide '<<' and '>>' for your 'Matrix'.
//
// [3] Make the representation of 'Matrix' private.
//     What would be a more complete set of members for 'Matrix'?
//     For example, would you like a '+=' operator?
//     What would be a good set of constructors?
//     Make a list and give a brief argument for each operation.
//     Implement and test your more complete 'Matrix'.
//
//     Additions:
//         - '+=' operator
//         - Subscripting using index
//         - Member functions 'size()', 'rowSize()', and 'columnSize()' to access member data
//         - Range-checked initializer list added to constructor (empty by default)
//
// [4] Implement a 'row(i)' member function that returns a 'vector' that is a copy of the ith row.
//     Implement a 'column(i)' member function that returns a 'vector' that is a copy of the ith column.
//

#include "PPPheaders.h"


class Matrix
{
public:
	Matrix(const unsigned int &a_rows, const unsigned int &a_columns, initializer_list<double> lst = {})
		:m_row_size(a_rows),
		m_column_size(a_columns)
	{
		if (!m_row_size || !m_column_size)
			throw logic_error("invalid matrix dimensions");

		if (a_rows > SIZE_MAX / a_columns)		// Will a_rows * a_columns overflow?
			throw overflow_error("matrix dimensions would overflow");
		
		m_vec.resize(a_rows * a_columns, 0.0);	// Initialize elements to 0.0

		// Copy lst into m_vec
		if (lst.size())
		{
			// Get delta to prevent memory corruption
			int d_size = m_vec.size() - lst.size();
			if (d_size < 0)
				copy(lst.begin(), lst.end() + d_size, m_vec.data());	// Add negative difference to lst.end() so that overflowing values are discarded

			else
				copy(lst.begin(), lst.end(), m_vec.data());
		}
	}

	Matrix() = delete;

	Matrix(const Matrix &) = default;

	~Matrix() = default;



	Matrix &operator=(const Matrix &) = default;

	// Subscript using coordinates
	double &operator()(const unsigned int &a_row, const unsigned int &a_column)
	{
		if (a_row >= m_row_size || a_column >= m_column_size)
			throw range_error("subscript range error");

		return m_vec.at(a_row * m_column_size + a_column);
	}

	const double &operator()(const unsigned int &a_row, const unsigned int &a_column) const
	{
		if (a_row >= m_row_size || a_column >= m_column_size)
			throw range_error("subscript range error");

		return m_vec.at(a_row * m_column_size + a_column);
	}

	// Subscript using index
	double &operator[](const size_t &a_index)
	{
		if (a_index >= m_vec.size())
			throw range_error("subscript range error");

		return m_vec.at(a_index);
	}
	
	const double &operator[](const size_t &a_index) const
	{
		if (a_index >= m_vec.size())
			throw range_error("subscript range error");

		return m_vec.at(a_index);
	}

	bool operator==(const Matrix &a_matrix) const
	{
		return (a_matrix.m_row_size == m_row_size &&
				a_matrix.m_column_size == m_column_size &&
				a_matrix.m_vec == m_vec);
	}

	Matrix operator+(const Matrix &a_matrix) const
	{
		if (a_matrix.m_row_size != m_row_size ||
			a_matrix.m_column_size != m_column_size)
			throw logic_error("matrices have different dimensions");

		Matrix temp_matrix{ m_row_size, m_column_size };

		for (size_t i = 0; i < size(); ++i)
			temp_matrix[i] = m_vec.at(i) + a_matrix.m_vec.at(i);

		return temp_matrix;
	}

	Matrix &operator+=(const Matrix &a_matrix)
	{
		*this = *this + a_matrix;
		return *this;
	}

	friend ostream &operator<<(ostream &os, const Matrix &a_matrix)
	{
		for (size_t i = 0; i < a_matrix.size(); ++i)
		{
			if ((i + 1) % a_matrix.columnSize() == 0 && i)
				os << a_matrix[i] << endl;
			else
				os << a_matrix[i] << ' ';
		}
		return os;
	}

	friend istream &operator>>(istream &is, Matrix &a_matrix)
	{
		double inp = 0.0;
		for (size_t i = 0; is >> inp; ++i)
		{
			if (i >= a_matrix.size())
			{
				cerr << "matrix at maximum capacity!" << endl;
				break;
			}

			a_matrix[i] = inp;
		}
		
		return is;
	}


	size_t size() const
	{
		return m_vec.size();
	}

	unsigned int rowSize() const
	{
		return m_row_size;
	}

	unsigned int columnSize() const
	{
		return m_column_size;
	}

	vector<double> row(const unsigned int &a_row) const
	{
		if (a_row >= m_row_size)
			throw range_error("row argument out of range");
		
		vector<double> res_vec;
		for (size_t i = 0; i < size(); ++i)
			if (i % m_column_size == 0)
				res_vec.push_back(m_vec[i]);

		return res_vec;
	}

	vector<double> column(const unsigned int &a_column) const
	{
		if (a_column >= m_column_size)
			throw range_error("column argument out of range");

		vector<double> res_vec(m_column_size);
		auto new_begin = m_vec.begin() + a_column * m_column_size;
		auto new_end = new_begin + m_column_size;
		
		copy(new_begin, new_end, res_vec.data());

		return res_vec;
	}

private:
	unsigned int m_row_size;
	unsigned int m_column_size;
	vector<double> m_vec;
};

void test()
{
	random_device r;
	default_random_engine gen{ r() };
	uniform_real_distribution<double> dist(0., 99.9);

	// Constructor
	Matrix m1{ 6, 9 };
	Matrix m2{ 7, 3 };

	// Assignment & subscripting by index
	for (size_t i = 0; i < (m1.size() >= m2.size() ? m1.size() : m2.size()); ++i)
	{
		if (i < m1.size())
		{
			m1[i] = dist(gen);
			cout << m1[i] << ' ';
		}

		if (i < m2.size())
		{
			m2[i] = dist(gen);
			cout << m2[i];
		}
		cout << endl;
	}

	// Equality
	cout << boolalpha << (m1 == m2) << endl;

	// Copy constructor
	Matrix m3 = m1;

	cout << boolalpha << (m1 == m3) << endl;

	// Assignment & subscripting by coordinates
	cout << "Before: " << m1(0, 0) << '|' << m2(0, 0) << endl;
	m1(0, 0) = dist(gen);
	m2(0, 0) = dist(gen);
	cout << "After: " << m1(0, 0) << '|' << m2(0, 0) << endl;

	// Subscripting by coordinates
	for (short i = 0; i < 10; ++i)
	{
		cout << "m1 val: " << m1(random_int(m1.rowSize() - 1), random_int(m1.columnSize() - 1)) << endl;
		cout << "m2 val: " << m2(random_int(m2.rowSize() - 1), random_int(m2.columnSize() - 1)) << endl << endl;
	}

	// Addition
	m1 += m3;
	for (size_t i = 0; i < m1.size(); ++i)
		cout << m1[i] << endl;

	// Output
	Matrix m4{ 10, 10 };
	cout << "Matrix 1:\n" << m1;
	cout << "Matrix 2:\n" << m2;
	cout << "Matrix 3:\n" << m3;
	cout << "Matrix 4:\n" << m4;

	// Input
	Matrix m5{ 3, 4 };
	cout << "Enter some values (max. 25) >";
	//cin >> m5;

	cout << "Matrix 5:\n" << m5 << endl;

	// Matrix::row()
	vector<double> row_vec = m1.row(0);
	for (auto d : row_vec)
		cout << d << ' ';
	cout << endl;

	// Matrix::column()
	vector<double> column_vec = m1.column(0);
	for (auto d : column_vec)
		cout << d << ' ';
	cout << endl;

	// Initialize using list
	Matrix m6{ 2, 2, { 0.1, 1.4, 2.67 } };
	cout << "Matrix 6:\n" << m6;
}

int main()
{
	try
	{
		test();
	}
	catch (const logic_error &err)
	{
		cerr << "Logic error: " << err.what() << endl;
	}
	catch (const overflow_error &err)
	{
		cerr << "Overflow error: " << err.what() << endl;
	}
	catch (const range_error &err)
	{
		cerr << "Range error: " << err.what() << endl;
	}
	catch (...)
	{
		cerr << "Unknown error" << endl;
	}
}

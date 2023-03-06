#ifndef MATRIX_H
#  define MATRIX_H
#include <initializer_list>
#include <algorithm>
#include <array>
#include <memory>
#include <numeric>
#include <iostream>
#include <sstream>
#include <iomanip>

#undef minor // Some compilers have a macro named minor

using std::initializer_list;
using std::array;
using std::unique_ptr;
using std::max_element;
using std::accumulate;
using std::inner_product;
using std::ostream;
using std::ostringstream;
using std::streamsize;
using std::setw;
using std::endl;
using std::max;


namespace mpcs51044_norm {

template<int rows, int cols = rows>
class Matrix {
public:
	//////////////////////////////////////////
	// STATIC_ASSERT: a way to generate readable errors when using templates improperly
	//////////////////////////////////////////
	static_assert(rows == cols,	"Sorry, only square matrices have determinants");
	Matrix() : data{} {}

	// constructor takes a std::initializer_list<T>, which
	// represents a “braced initializer of Ts” expression

	// Initializer lists have begin(), end(), and size()
	// methods so your constructor can iterate through their value.
	Matrix(initializer_list<initializer_list<double>> init) {
		auto dp = data.begin();
		for (auto row : init) {
			std::copy(row.begin(), row.end(), dp->begin());
			dp++;
		}
	}

	// operator() overload...fetch data
	double &operator()(int x, int y) {
		return data[x][y];
	}

	// operator() overload...fetch data
	double operator()(int x, int y) const {
		return data[x][y];
	}

	// function to print itself
	inline friend
		ostream &
		operator<<
		(ostream &os, const Matrix<rows, cols> &m) {
		size_t width = m.longestElementSize() + 2;
		os << "[ " << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				os << setw(static_cast<streamsize>(width)) << m(i, j);
			}
			os << endl;
		}
		os << "]" << endl;
		return os;
	}

	// minor()
	Matrix<rows - 1, cols - 1> minor(int r, int c) const {
		Matrix<rows - 1, cols - 1> result;
		for (int i = 0; i < rows; i++) {
			if (i == r) {
				continue;
			}
			for (int j = 0; j < cols; j++) {
				if (j == c) {
					continue;
				}
				result(i < r ? i : i - 1, j < c ? j : j - 1) = data[i][j];
			}
		}
		return result;
	}

	// determinant()
	double determinant() const {
		double val = 0;
		for (int i = 0; i < rows; i++) {
			val += (i % 2 ? -1 : 1)
				* data[i][0]
				* minor(i, 0).determinant();
		}
		return val;
	}

	// overload operator+()... for addition
	Matrix &operator+=(Matrix const &other) {
		*this = *this + other;
		return *this;
	}

private:
	static size_t accumulateMax(size_t acc, double d) {
		ostringstream ostr;
		ostr << d;
		return std::max(acc, ostr.str().size());
	}
	static size_t accumulateMaxRow(size_t acc, array<double, cols> row) {
		return std::max(acc, accumulate(row.begin(), row.end(), static_cast<size_t>(0), accumulateMax));
	}
	size_t longestElementSize() const {
		return accumulate(data.begin(), data.end(), 0, accumulateMaxRow);
	}
	array<array<double, cols>, rows> data;
};

// template specialization: implement specialized method for a Matrix<1,1>
template<>
double
Matrix<1, 1>::determinant() const
{
	return data[0][0];
}

// template specialization: implement specialized method for a Matrix<2,2>
template<>
double
Matrix<2, 2>::determinant() const
{
	return data[0][0]*data[1][1] - data[1][0]*data[0][1];
}

// overload operator*()... for multiplication
template<int a, int b, int c>
inline Matrix<a, c>
operator*(Matrix<a, b> const &l, Matrix<b, c> const &r)
{
	Matrix<a, c> result;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < c; j++) {
			double total = 0;
			for (int k = 0; k < b; k++)
				total += l(i, k) * r(k, j);
			result(i, j) = total;
		}
	}
	return result;
}

// overload operator+()... for addition
template<int a, int b>
inline Matrix<a, b>
operator+(Matrix<a, b> const &l, Matrix<a, b> const &r)
{
	Matrix<a, b> result;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < c; j++) {
			result(i, j) = l(i,j) + r(i,j);
		}
	}
	return result;
}

}
#endif
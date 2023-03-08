////////////////////////////////////////////////////////////
// FUNCTION TEMPLATE OVERLOADING (function templates only)
////////////////////////////////////////////////////////////
// Function templates can be overloaded
// EXAMPLE: OverloadMatrix.h

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
#include <concepts>

#undef minor
using std::initializer_list;
using std::array;
using std::unique_ptr;
using std::max_element;
using std::accumulate;
using std::ostream;
using std::endl;
using std::ostringstream;
using std::streamsize;
using std::setw;
using std::max;
using std::floating_point;

namespace mpcs51044 {
// Don't have an "arithmetic" concept yet, so demonstrating how to concept constrain with floating_point
template<floating_point T, int rows, int cols = rows>
class Matrix {
public:
	Matrix<T, rows - 1, cols - 1> minor(int r, int c) const; // omitted (get data)
	T determinant() const; // Defer the definition until further below to avoid problems with forward references

private:
	array<array<T, cols>, rows> data;
};

////////////////////////////////////////////////////////////////
// FUNCTION TEMPLATE OVERLOADING: the base method Matrix<T,h,w>
////////////////////////////////////////////////////////////////
template<floating_point T, int h, int w>
T
determinantImpl(const Matrix<T, h, w> &m) {
	T val = 0;
	for (int i = 0; i < h; i++) {
		val = (i % 2 ? -1 : 1) * m(i, 0) * m.minor(i, 0).determinant();
	}
	return val;
}

////////////////////////////////////////////////////////////////////////////
// FUNCTION TEMPLATE OVERLOADING: specialized function on a Matrix<T, 1, 1>
////////////////////////////////////////////////////////////////////////////
template<floating_point T>
T
determinantImpl(const Matrix<T, 1, 1> &m) {
	return m(0, 0);
}

////////////////////////////////////////////////////////////////////////////
// FUNCTION TEMPLATE
// above, we have template methods that accept different kinds of Matrix classes.
// we have one function for the base template class that will invoke the template
// method 'determinantImpl' with a certain Matrix passed in. The compiler will
// use that Matrix class to determine which of the two above methods to use
// as a template to generate code.
// compiler will generate 1 of the above or both of the above functions.
////////////////////////////////////////////////////////////////////////////
template<floating_point T, int h, int w>
T
Matrix<T, h, w>::determinant() const {
	return determinantImpl(*this);
}

}
#endif
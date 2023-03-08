//////////////////////////////////////////////////
// FULL SPECIALIZATION (function, class, or member)
//////////////////////////////////////////////////
// A function, class, or member can be fully specialized
// see Matrix<1,1>::determinant() in Matrix.h

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


namespace mpcs51044 {

template<int rows, int cols = rows>
class Matrix {
public:
	//////////////////////////////////////////////////////////////////////////////////
	// METHOD FOR TEMPLATE CLASS: Matrix<rows,cols>
	// this is the standard method for the class
	//////////////////////////////////////////////////////////////////////////////////
	double determinant() const {
		double val = 0;
		for (int i = 0; i < rows; i++) {
			val += (i % 2 ? -1 : 1)
				* data[i][0]
				* minor(i, 0).determinant();
		}
		return val;
	}
	//////////////////////////////////////////////////////////////////////////////////

private:
	array<array<double, cols>, rows> data;
};

//////////////////////////////////////////////////////////////////////////////////
// FULL TEMPLATE SPECIALIZATION: implement a method uniquely for the class: Matrix<1,1>
// this is the standard method for this specific class: Matrix<1,1>
// i.e. we are writing a uniquely different function for the class Matrix<1,1>
//////////////////////////////////////////////////////////////////////////////////
template<>
double
Matrix<1, 1>::determinant() const {
	return data[0][0];
}
//////////////////////////////////////////////////////////////////////////////////

}
#endif
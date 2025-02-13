//////////////////////////////////////////
// PARTIAL SPECIALIZATION (classes only)
//////////////////////////////////////////
// Template class:
template<class T, class U>
class Foo { /*...*/ };

// Partial specialization:
template<class T>
class Foo<T, int> {...};
// You can tell the second is a specialization because of the <> after the class name
// The partially specialized class has no particular relation to the general template class
// In particular, you need to either redefine (bad) or inherit (good) common functionality

// EXAMPLE: PSMatrix.h
#ifndef MATRIX_H
#  define MATRIX_H
#include <initializer_list>
#include <algorithm>
#include <array>
#include <memory>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <iostream>
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

namespace mpcs51044 {

////////////////////////////////////
// BASE CLASS WITH COMMON BEHAVIOR
////////////////////////////////////
template<typename T, int rows, int cols = rows>
class MatrixCommon {
public:
	// MatrixCommon(initializer_list<initializer_list<T>> init); // omitted
	// MatrixCommon() : data{} {}; // no arg constructor
	// T &operator()(int x, int y);         // omitted 
	// T operator()(int x, int y) const;    // omitted
	// inline friend ostream &	operator<<(ostream &os, const MatrixCommon<T, rows, cols> &m); // omitted

protected:
	array<array<T, cols>, rows> data;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
// MATRIX CLASS. adds new methods: minor(), determinant() to templace class MatrixCommon<T, rows, cols>
////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, int rows, int cols = rows>
class Matrix : public MatrixCommon < T, rows, cols > {
public:
	// Matrix() = default;;
	// Matrix(initializer_list<initializer_list<T>> init) : MatrixCommon<T, rows, cols>(init) {};
	Matrix<T, rows - 1, cols - 1> minor(int r, int c) const; // omitted
	T determinant() const {
		T val = 0;
		for (int i = 0; i < rows; i++) {
			val += (i % 2 ? -1 : 1)
				* MatrixCommon<T, rows, cols>::data[i][0]
				* minor(i, 0).determinant();
		}
		return val;
	}
};

////////////////////////////////////////////////////////////////////////////
// PARTIAL SPECIALIZATION: specialized class for the MatrixCommon<T, 1, 1>
////////////////////////////////////////////////////////////////////////////
template<typename T>
class Matrix<T, 1, 1> : public MatrixCommon < T, 1, 1 > {
public:
	// Matrix() = default;
	// Matrix(initializer_list<initializer_list<T>> init) : MatrixCommon<T, 1, 1>(init) {}

	T determinant() const {
		return this->data[0][0];
	}
};

}
#endif
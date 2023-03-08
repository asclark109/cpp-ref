#ifndef EXINLINE_FRIEND_H
#  define EXINLINE_FRIEND_H

#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>

// may want to write a custom print to console method for a class. e.g Triangle
std::ostream& operator<<(std::ostream &os, Triangle const &triangle);
// the first argument is std::ostream&, which means we would have 
// to make it a member of class std::ostream, unfortunately

// so, when you want to do an implementation for your class, you'll need to
// define it as a global method.

// C++ lets us put global functions inside the class
// definition as long as we precede it by "inline friend"

size_t numDigits(int i) {
	std::ostringstream os;
	os << i;
	return os.str().size();
}

class Triangle {
public:
	Triangle(int n);
private:
	// Only the class implementer can declare who its friends are.
	// use the friend keyword and the name of a non-member function 
	// or other class to grant it access to the private and protected
	// members of your class. grant ostream's operator << friend level
	// access to this class
	friend std::ostream &operator<<(std::ostream &, Triangle); // DECLARE FRIEND METHOD
	void addRow() {
		Row row = rows[rows.size() - 1];
		Row result;
		int previous = 0;
		for (auto current: row) {
			result.push_back(previous + current);
			previous = current;
		}
		result.push_back(previous);
		rows.push_back(result);
	}

    int maxElement() const {
		Row lastRow = rows[rows.size() - 1];
		return *max_element(lastRow.begin(), lastRow.end());
	}

	std::string centeredInt(int i) {
		std::ostringstream os;
		os << i;
		std::string str = os.str();
		return std::string((eltSize - str.size())/2, ' ') + str;
	}

	void printRow(int i)	{
		Row row = rows[i];
		for(auto elt: row) {
			std::cout << std::left << std::setw(eltSize) << centeredInt(elt) << " ";
		}
		std::cout << std::endl;
	}
	typedef std::vector<int> Row;
	std::vector<Row> rows;
	size_t eltSize;
};


int constexpr rows = 12;

Triangle::Triangle(int n) {
	Row startingRow; // Get things started
	startingRow.push_back(1); // With a row with only a 1
	rows.push_back(startingRow);
	for(int i = 1; i < n; i++) {
		addRow();
	}
	eltSize = numDigits(maxElement());
}

// An inline function is one for which the compiler copies the code from 
// the function definition directly into the code of the calling function
// rather than creating a separate set of instructions in memory. This
// eliminates call-linkage overhead and can expose significant optimization
// opportunities. Using the "inline" specifier is only a suggestion to 
// the compiler that an inline expansion can be performed; the compiler
// is free to ignore the suggestion
// EFFECTS OF INLINING
// (1) In most cases, inlining increase program size. But in some cases,
//     when the function size is smaller than the function call code size,
//     inlining could reduce program size.
// (2) In most cases, inlining could improve execution time by avoiding
//     the call overhead, and possible see-through by the optimizer (making
//     it a non-opaque function) for more optimizing opportunities. However,
//     if the function is not called frequently, it will not have visible 
//     runtime improvement.
// (3) Inlining increases practical coupling by making the caller 
//     potentially rely on the inlined code's internal implementation details.
//     The problem with practical coupling is that when the inlined callee
//     changes, you have to recompile the caller. This is a cost to build
//     and development time.
inline std::ostream& operator<<(std::ostream &os, Triangle triangle) { // INLINE METHOD
    for(int i = 0; i < rows; i++) {
        std::string spaces((rows - i - 1) * (triangle.eltSize + 1) / 2, ' ');
        os << spaces;
        triangle.printRow(i);
    }
	return os;
}


#endif
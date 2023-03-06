#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
using namespace std;

size_t
numDigits(int i)
{
	ostringstream os;
	os << i;
	return os.str().size();
}

class Triangle {
public:
	Triangle(int n);
private:
	friend ostream &operator<<(ostream &, Triangle);
	void addRow()
	{
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

	string centeredInt(int i)
	{
		ostringstream os;
		os << i;
		string str = os.str();
		return string((eltSize - str.size())/2, ' ') + str;
	}

	void
	printRow(int i)
	{
		Row row = rows[i];
		for(auto elt: row) {
			cout << left << setw(eltSize) << centeredInt(elt) << " ";
		}
		cout << endl;
	}
	typedef vector<int> Row;
	vector<Row> rows;
	size_t eltSize;
};


int constexpr rows = 12;

Triangle::Triangle(int n)
{
	Row startingRow; // Get things started
	startingRow.push_back(1); // With a row with only a 1
	rows.push_back(startingRow);
	for(int i = 1; i < n; i++) {
		addRow();
	}
	eltSize = numDigits(maxElement());
}

inline ostream&
operator<<(ostream &os, Triangle triangle)
{
    for(int i = 0; i < rows; i++) {
        string spaces((rows - i - 1) * (triangle.eltSize + 1) / 2, ' ');
        os << spaces;
        triangle.printRow(i);
    }
	return os;
}


int
main()
{
    Triangle triangle(rows);
    cout << triangle;
    return 0;
}

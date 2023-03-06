#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
// #include <format>
using namespace std;

using Row = vector<int>; // Row is a synonym for vector<int>
// typedef vector<int> Row;  // Old-fashioned version you might see sometimes
using Triangle = vector<Row>;

Row
nextRow(Row row)
{
    Row result;
    int previous = 0;
    for (auto elt : row) {
        result.push_back(previous + elt);
        previous = elt;
    }
    result.push_back(previous);
    return result;
}

int constexpr rows = 20; 

int numDigits(int i)
{
    return std::to_string(i).size();
}

int eltSize;

// void
// printRow(ostream& os, Row row)
// {
//     for (auto elt : row) {
//         os << format("{:^{}}", elt, eltSize) << " ";
//     }
//     os << endl;
// }

// This is type-unsafe! Triangle should be a class. HW 2.4 fixes
ostream&
operator <<(ostream& os, Triangle triangle)
{
    Row lastRow = triangle[rows - 1];

    int maxElement = *max_element(lastRow.begin(), lastRow.end());
    eltSize = numDigits(maxElement);
    for (int i = 0; i < rows; i++) {
        string spaces((rows - i - 1) * (eltSize + 1) / 2, ' ');
        os << spaces;
        // printRow(os, triangle[i]);
    }
    return os;
}


int
main()
{
    Triangle triangle;
    Row previousRow = { 1 };
    for (int i = 0; i < rows; i++) {
        triangle.push_back(previousRow);
        previousRow = nextRow(previousRow);
    }
    cout << triangle;
    return 0;
}

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
// #include <format>
#include <sstream>
#include <algorithm>

int factorial(int n) {
	if (n == 1 || n == 0) {
		return 1;
	}
	else {
		return n * factorial(n - 1);
	}
}

int nChooseK(int n, int k) {
	return factorial(n) / (factorial(k) * factorial(n - k));
}

std::string toStr(int x) {
	return std::to_string(x);
}

class PascalRow {
private:
	std::vector<int> terms;
public:
	PascalRow(int nth) {
		int n = nth - 1; // e.g. n==2 in 3rd row
		for (int k = 0; k <= n; k++) {
			terms.push_back(nChooseK(n, k));
		}
	}
	PascalRow() {}; // need to include this to prevent "no default constructor bug"

	std::vector<int> termsAsInts() {
		return terms;
	}

	std::vector<std::string> termsAsStrings() {
		std::vector<std::string> termsAsStrs(terms.size());
		std::transform(terms.begin(), terms.end(), termsAsStrs.begin(), toStr);
		return termsAsStrs;
	}

	std::string toRowStr() {
		std::stringstream ss;
		for (auto number : terms)
		{
			ss << " " << number;
		}
		return ss.str();
	}

	int size() {
		return terms.size();
	}
};

class PascalTriangle {
private:
	std::vector<PascalRow> pascalRows;
public:
	PascalTriangle(int nRows) {
		pascalRows.resize(nRows); // resize rows to have enough space
		for (int i = 0; i < nRows; i++)
		{
			pascalRows[i] = PascalRow(i + 1);
		}
	};

	// draws self to console in a simple way
	void drawSimple() {
		for (PascalRow row : pascalRows) {
			std::cout << row.toRowStr() << std::endl;
		}
	}

	// draws self to console in a pretty way
	void drawFancy() {
		// (1) find the number (which is a string) with the largest width
		// (2) set the width of future blocks to be 2+largest_width
		// (3) organize numbers from each row into blocks, with centering.
		// (4) build the triangle as a row of blocks

		// (1)
		// assume largest character width can be found with final row
		int largestWidth = 1;
		for (std::string number : pascalRows.back().termsAsStrings()) {
			largestWidth = number.size() > largestWidth ? number.size() : largestWidth;
		}
		int numElems = pascalRows.back().size(); // number of blocks that will be needed for each row

		// (2)
		int blockWidth = largestWidth + 2; // e.g. " 30 " so 4

		// (3)
		std::vector<std::vector<std::string>> blockRows; // stores rows of blocks, which are strings padded w/ whitespace
		for (PascalRow pascalRow : pascalRows) {
			std::vector<std::string> blocks;
			for (std::string number : pascalRow.termsAsStrings()) {
				// blocks.push_back(std::format("{:^{}}", number, blockWidth));
			}
			blockRows.push_back(blocks);
		}
		// now:
		// 1
		// 1    1
		// 1    2    1
		// 1    3    3    1
		// 1    4    6    4    1
		// 1    5    10   10   5    1
		// 1    6    15   20   15   6    1
		// 1    7    21   35   35   21   7    1

		// (4)
		int lastRowWidth = numElems * blockWidth;
		bool isLengthOdd = !(lastRowWidth % 2 == 0);

		for (std::vector<std::string> blocks : blockRows) {
			// print row
			// determine padding
			int widthOfBlocksInRow = blocks.size() * blockWidth;
			int remainingSpace = lastRowWidth - widthOfBlocksInRow;

			// print left padding
			std::cout << std::string(remainingSpace / 2, ' ');

			// print blocks
			for (std::string number : blocks) {
				std::cout << number;
			}

			// print right padding
			if (remainingSpace % 2 == 1) {
				std::cout << std::string(remainingSpace / 2 + 1, ' ') << '\n';
			}
			else {
				std::cout << std::string(remainingSpace / 2, ' ') << '\n';
			}
		}
	}

};


int main()
{
	constexpr int NUM_ROWS = 13;
	PascalTriangle triangle = PascalTriangle(NUM_ROWS);
	triangle.drawFancy();

	return 0;
}

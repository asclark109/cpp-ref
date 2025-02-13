////////////////////////////
// INHERITING CONSTRUCTORS
////////////////////////////
// It seems annoying that in PSMatrix, we can inherit
// everything but constructors from the common
// implementation even though they do the right thing

// Indeed, the constructors don't even have the same names,
// because they are named after the class

// Since classes often have many constructors, this can make it
// painful to build lightweight wrapper classes on top of others

//  We can solve this by saying we want to inherit constructors

template<typename T, int rows, int cols = rows>
class Matrix : public MatrixCommon < T, rows, cols > {
public:
	// Matrix() = default;
	// Matrix(initializer_list<initializer_list<T>> init) : MatrixCommon<T, rows, cols>(init) {}
    ////////////////////////////
    // INHERITING CONSTRUCTOR
    ////////////////////////////
    using MatrixCommon<T, rows, cols>::MatrixCommon;

	Matrix<T, rows - 1, cols - 1> minor(int r, int c) const {
		Matrix<T, rows - 1, cols - 1> result;
		for (int i = 0; i < rows; i++) {
			if (i == r) {
				continue;
			}
			for (int j = 0; j < cols; j++) {
				if (j == c) {
					continue;
				}
				result(i < r ? i : i - 1, j < c ? j : j - 1) = this->data[i][j];
			}
		}
		return result;
	}
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
//////////////
// DECLTYPE
//////////////

// Sometimes you want to know the type of a value
// Suppose I don’t know what type an expression x is

// Very possible in template code or with complex expressions
// (e.g., the type of 1u + 'c' is implementation-defined depending on whether
// char is signed or unsigned)

// decltype(x) gives you the type of x

template<class T, int rows, int cols = rows>
class Matrix {};

void exHiddenBug(){    
    int x{0};
    Matrix<decltype(x), 1, 2> m = { };
}
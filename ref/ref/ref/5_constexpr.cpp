#include <iostream>

////////////////
// CONSTEXPR
////////////////
// Template arguments need to be known at compile time 
// consider the following that won't compile at runtime

template<int rows, int cols = rows>
class Matrix {};

void exHiddenBug(){    
    int n;
    std::cout << "How big a matrix? ";
    std::cin >> n;
    // Matrix<n, n> m; // Ill-formed! must have constant value
}
// Since we don’t know n at compiletime, the compiler can’t compile the class Matrix<n, n>

// But doing things at compile-time can also help performance!!!

////////////////////////
// CONSTANT EXPRESSIONS
////////////////////////
// A constant expression is an expression that can be evaluated at compile-time.
// Built-in values like 3, 2*7 and false are constant expressions.
// But since templates and performance programming are so important in C++, we would
// like to be able to create our own constant expressions.
// That is what constexpr does

////////////////
// CONSTEXPR
////////////////
int constexpr seven = 7; // immutable
// wherever the compiler sees seven, it can substitute the constant expression 7
// constexpr functions

double const pi = 4*atan(1);
// Wouldn’t it be nice if that could be calculated at compile-time?
// To say that a function is computable at compiletime, label it as constexpr
int constexpr gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a%b);
}
// If the arguments are known at compile-time, the function may be run either at compile-time or at
// run time at the compiler’s discretion. E.g., gcd(34, 55)

// If the value is needed at compile-time, it is calculated by the compiler. 
// E.g., as a non-type template parameter: Matrix<gcd(34, 55)>

// If its arguments are not known at compile-time, it won’t be run until run-time:
// void f(int i) {
//     return gcd(34, i); // i is unknown
// }

// A constexpr function cannot contain just any code.

// if it contained a thread_local variable, what would that mean at compile-time?
////////////////
// NOT ALLOWED
////////////////
// -- Uninitialized declarations
// -- static or thread_local declarations
// -- Modification of objects that were not created in the function
// -- Or potential modifications by, say, calling a non-constexpr function.
// -- virtual methods
// -- Non-literal return types or parameters
// -- A type is literal if its constructor is trivial or constexpr
constexpr auto square(int x) { 
    return x*x;
}
Matrix<square(3), square(3)> m;

//////////////////
// if constexpr
//////////////////
// Saying 'if constexpr' rather than just 'if' tells the compiler
// that if it can compute the result at compile time, do so and
// consider skipping (rejecting) a branch so it will never compile

// Just replacing the if with if constexpr makes it work

// No specialization or overloading required
template<int r, int c = r>
class Matrix {
    /* ... */
    double determinant() {
        ////////////////////
        // IF CONSTEXPR
        ////////////////////
        if constexpr (r == 1 && c == 1) // 1x1 Matrix  WE KNOW THIS WILL NEVER RUN
            return data[0][0];
        else {
            double val = 0; // Bigger. Use formula
            for (int i = 0; i < r; i++) {
                val += (i % 2 ? -1 : 1) * data[i][0]
                * minor(i, 0).determinant();
            }
        }
        return val;
    }
};

////////////////////////
// `constexpr` vs `const`
////////////////////////
// It is easy to confuse const and constexpr, but they mean different things
// constexpr means the value is known at compiletime
int constexpr eight = 8; // seven means 7
// const means the value won’t be changed
void f(int const &i);
// We don’t know the value of i until runtime, but we know f won’t change it
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
void f(int const & i);
// We don’t know the value of i until runtime, but we know f won’t change it
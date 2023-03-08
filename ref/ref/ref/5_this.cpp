#include "ex_4_PSMatrix.h"

////////////
// *this
////////////
// Sometimes a method needs a reference to the object it is a part of

// In OverloadMatrix, Matrix::determinant() uses this to pass the
// containing Matrix to the external determinantImpl function
template<class T, int h, int w>
T
mpcs51044_ps::Matrix<T, h, w>::determinant() const
{
    return determinantImpl(*this);
}
// This also comes in handy in the homework for overloading Matrix::operator+=
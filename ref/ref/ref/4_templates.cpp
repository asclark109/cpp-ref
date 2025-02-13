#include <concepts>

// There are 

// (1) FUNCTION TEMPLATES, like std::sort
// (2) CLASS    TEMPLATES, like std::vector
// (3) VARIABLE TEMPLATES

//////////////////////
// FUNCTION TEMPLATES
//////////////////////
// For function templates, we could simply use “concept auto” arguments

//////////////////////
// CLASS TEMPLATES
//////////////////////
// there are no “arguments,” so you put them up front in a “template” header
template<std::floating_point T> // Good design. using a concept to constrain
struct complex; 

template<typename T>
struct vector { /* ... */ };    // Basic design. no constraints.


////////////////////////////////////////////
// SPECIALIZING AND OVERLOADING TEMPLATES
////////////////////////////////////////////

// The “secret sauce” for C++ templates is that
// if the general “generic” definition of the
// template isn’t really what you want for a
// particular set of template parameters, you
// can override it for that particular case with a
// specialization

// Think of this as the compile-time analog to
// object orientation where you also override a
// more general method in a more specialized
// derived class

//////////////////////////
// FULL SPECIALIZATION
//////////////////////////
// see Matrix<1,1>::determinant() in Matrix.h


//////////////////////////
// FUNCTION TEMPLATE OVERLOADING
//////////////////////////
// For example, see OverloadMatrix.h


//////////////////////////
// PARTIAL SPECIALIZATION
//////////////////////////
// Only classes may be partially specialized

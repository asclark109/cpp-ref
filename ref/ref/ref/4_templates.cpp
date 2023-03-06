#include <concepts>

// There are 

// FUNCTION TEMPLATES, like std::sort
// CLASS TEMPLATES, like std::vector
// VARIABLE templates

//////////////////////
// FUNCTION TEMPLATES
//////////////////////
// For function templates, we could simply use “concept auto” arguments

//////////////////////
// CLASS TEMPLATES
//////////////////////
// there are no “arguments,” so you put them up front in a “template” header
template<std::floating_point T> struct complex; // use a concept to constrain
template<typename T> struct vector { /* ... */ };  // no constraints

//

// Specializing and overloadingtemplates

// The “secret sauce” for C++ templates is that
// if the general “generic” definition of the
// template isn’t really what you want for a
// particular set of template parameters, you
// can override it for that particular case with a
// specialization
// ⚫ Think of this as the compile-time analog to
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
// Template class:
template<class T, class U>
class Foo { /*...*/ };

// Partial specialization:
template<class T>
class Foo<T, int> {...};
// You can tell the second is a specialization because of the <> after the class name

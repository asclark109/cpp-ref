

//////////////////////
// STATIC_ASSERT
//////////////////////
// C++ lets you create a compile-time assertion
// that prints a nice error message of your
// choice
// 

template<int rows, int cols = rows>
class Matrix {
public:
	//////////////////////////////////////////
	// STATIC_ASSERT: a way to generate readable errors when using templates improperly
	// for the template argument combinations? use concepts for what those template argument
	// types ought to satisfy
	//////////////////////////////////////////
	static_assert(rows == cols,	"Sorry, only square matrices have determinants");
	Matrix() : data{} {}
};

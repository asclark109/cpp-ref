// 3 WAYS OF PASSING

#include <concepts>

// BY VALUE
// ⚫ The function gets its own copy
// ⚫ // Doesn’t change callers int
void f1(int i) { i += 2; }
// ⚫ By (lvalue) reference
// ⚫ The function works with the caller’s object
// ⚫ // Changes callers int
void f2(int &i) { i += 2; }
// ⚫ By rvalue reference
// ⚫ If the function is called on a temporary
// ⚫ // Can reuse parts from abandoned x
struct X{};
void f3(X &&x) { }

//////////////////
// RULE OF FIVE
//////////////////
// There is a lot of discussion about whether the rule of 3 should be extended to a “rule of 5,”

// If you define any of
// ⚫ The destructor
// ⚫ The copy constructor
// ⚫ Copy assignment operator
// ⚫ Move constructor
// ⚫ Move assignment operator
// You should review that they all do the right thing because they are all related

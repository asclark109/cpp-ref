
#include<iostream>

class A {
public:
	int num{ 0 };
	float preciseNum{ 10.20 };

	int DereferenceInteger(int* intPtr) {
		return *intPtr;
	}

	int reducepreciseNumToIntWithFloatToDoubleConverter(double (*theFunction)(float&)) {
		// accepts a function that converts a float to a double;
		// we use this function to convert a member variable of A called "preciseNum" from float to double,
		// which "widens" the precision, and then we use it to construct an int, which is a net-narrowing
		// of precision. we return the int to the client.
		double doubleResult{ (*theFunction)(preciseNum) };
		return int(doubleResult); // loss of precision
	}
};

void executeVoidFunc(void (*theFuncPtr)()) {
	(*theFuncPtr)();
}

void printHelloWorld() {
	std::cout << "hello world!" << std::endl;
}

double copyToLargerPrecision(float& theFloat) {
	return double(theFloat);
}

int get10() {
	return 10;
}

// returns the "larger" char
char* getBiggerChar(char* firstPtr, char* secondPtr) {
	return *firstPtr > * secondPtr ? firstPtr : secondPtr;
}

int main() {
	// Write a program that defines variables of each type set to some meaningful
	// value (You are highly encouraged to check with a compiler). 
	// If the type is callable, the program should call it.

	// int*
	int* intPtr = new int;

	// int&
	int i = 5;
	int& iRef = i;

	// double
	double d{ 4 }; // implicit type conversion of int to double

	// A* (A is any appropriate class).
	A* a = new A;

	// char const*
	char const* myCstring{ "C string literal" };

	// char const&
	char letter{ '3' };
	char const& letterRef = letter;

	// long[7]
	long big = 1'000'000'000'000'000;
	long arr[7] { big,big,big,big,big,big,big };

	// int**
	int* numPtr = new int{ 0 };
	int** numPtrPtr = &numPtr;

	// int*&
	int* num2Ptr = new int{ 0 };
	int*& num2PtrRef = num2Ptr;

	// float&
	float myFloat{ 1.0 };
	float& myFloatRef = myFloat;

	// int (*)() (See http ://www.newty.de/fpt/index.html)
	int(*funcPtr)() = get10;
	(*funcPtr)(); // returns 10

	// int (*&)()
	int(*&funcPtrRef)() = funcPtr;
	(*funcPtrRef)(); // also returns 10 (same as func above)
	
	// char* (*)(char*, char*)
	char*(*charCompareFunc)(char*, char*) = getBiggerChar;
	char* letter1 = new char{ 'L' };
	char* letter2 = new char{ 'M' };
	std::cout << "the bigger char between (L,M) is: " << *charCompareFunc(letter1, letter2) << std::endl;

	// int A::* (member accessor)
	int A::* aNumPtr = &A::num; // can now quickly access num attribute of A objects
	A* aPtr = new A;
	aPtr->*aNumPtr = 2; // sets the num attribute of the A object (*aPtr) to 2
	
	// int (A::*)(int*) 
	// "member function pointer" -- my own words
	int (A::*aFuncPtr)(int*) = &A::DereferenceInteger;
	int myInt{ 3 };
	(aPtr->*aFuncPtr)(&myInt); // calls member function DereferenceInteger and returns a dereferenced integer

	// int (A::**)(int*)
	// "a pointer to a member function pointer" -- my own words
	int (A::** aFuncPtrPtr)(int*) = &aFuncPtr;
	(aPtr->** aFuncPtrPtr)(&myInt); // same invocation as above but requires another dereferencing operator
	
	// int (A::*&)(int*)
	// "a reference to a member function pointer" -- my own words
	int (A:: * &aFuncPtrRef)(int*) = aFuncPtr;
	(aPtr->*aFuncPtrRef)(&myInt); // same as original invocation because this is simply a reference to the existing funcPtr

	// int (A::*)(double (*)(float&))
	// "a pointer to a member function that accepts a function pointer" - my own words
	int (A:: * aFuncPtr2)(double (*theFunction)(float&)) = &A::reducepreciseNumToIntWithFloatToDoubleConverter;
	A a2;
	a2.preciseNum = 4.302;
	(a2.*aFuncPtr2)(copyToLargerPrecision); // returns 4
	
	// void (*p[10]) (void (*)());
	// "an array of size 10 to pointers to void functions that accept a pointer to a void function" - my own words
	
	// create an array of 10 function pointers, which all point to the same function "executeVoidFunc", which executes
	// the void function passed as an argument to it. We then iterate through all the function pointers and :
	// dereference the funcPtr to obtain a function, which we execute by passing in a simple void function "printHelloWorld".
	// Effectively, we ask 10 function pointers referring to executeVoidFunc to execute printHelloWorld for us, resulting
	// in "hello world" getting printed 10 times to console

	// initialize the array of function pointers
	int const size{ 10 };
	void (*funcPtrArr[size])(void (*)()) = { };
	for (size_t i = 0; i < size; i++)
	{
		funcPtrArr[i] = &executeVoidFunc;
	}
	// dereference each function pointer, and use that function to execute printHelloWorld
	for (auto& funcPtr : funcPtrArr)
	{
		(*funcPtr)(printHelloWorld);
	}

	return 0;
}
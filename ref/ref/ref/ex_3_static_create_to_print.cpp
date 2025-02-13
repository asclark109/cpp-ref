#include <iostream>

struct ForcePrint {
	ForcePrint(std::string msg) { std::cout << msg << std::endl; }
};

ForcePrint myPrinter{ "Hello World!" }; // object created/destroyed at program start/end

int
main()
{
	return 0;
}

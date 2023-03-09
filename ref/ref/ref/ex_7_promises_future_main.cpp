#include <iostream>
#include <chrono>
#include <thread>
#include "ex_7_promise_future_austin.h"
using namespace std::chrono_literals;

int add(int x, int y) {
	std::this_thread::sleep_for(5s);
	return x + y;
}

int main() {
	// Demonstrate custom implementations for Future and Promise by:
	// (1) creating a Promise (give it a function to run)
	// (2) ask the Promise to create an associated Future
	// (3) Telling the Promise to store a result of computation (Promise::set_value())
	// (4) Confirm Future can fetch that result with Future::get()
	
	std::cout << "[impl] creating promise and future" << std::endl;
	Promise<int> pi{};
	Future<int> fi = pi.get_future();

	std::cout << "[impl] setting value in promise" << std::endl;
	pi.set_value(3);

	std::cout << "[impl] fetching result in future" << std::endl;
	std::cout << fi.get() << std::endl;
}
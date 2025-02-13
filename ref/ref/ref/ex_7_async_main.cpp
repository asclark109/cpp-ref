#include <iostream>
#include <chrono>
#include <thread>
#include "ex_7_async_austin.h"
using namespace std::chrono_literals;

int add(int x, int y) {
	std::this_thread::sleep_for(3s); // sleep for 3 seconds
	return x + y;
}

int main() {
	std::cout << "executing async func..." << std::endl;
	auto ft = my_async(add, 1, 1);
	std::cout << "waiting for async to finish and store result in future..." << std::endl;
	std::cout << ft.get() << std::endl;
}
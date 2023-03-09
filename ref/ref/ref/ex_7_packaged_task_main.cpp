#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include "ex_7_packaged_task_austin.h"
using namespace std::chrono_literals;

int add(int x, int y) {
	std::this_thread::sleep_for(3s); // wait 3 seconds
	return x + y;
}


int main() {
	// Demonstrate custom implementation for packaged_task by:
	// (1) creating a BasicPackagedTask (give it a function to run)
	// (2) ask the PackagedTask for an associated Future
	// (3) detach a thread that is given the BasicPackagedTask and executes it.
	// (4) in main, call Future::get(). Main should now block until the detached thread
	//     has completed computation of the task

	std::cout << "[main] creating promise and getting future..." << std::endl;
	BasicPackagedTask<int(int,int)> pt{add};
	auto fut = pt.get_future();

	std::cout << "[main] detaching a thread to execute promise..." << std::endl;
	std::thread([&]() {	pt(1, 2); }).detach();

	std::cout << "[main] getting result from future (this will block until future holds result from detached thread)..." << std::endl;
	std::cout << fut.get() << std::endl;
}
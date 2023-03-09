#ifndef ASYNC_H
#  define ASYNC_H

#include <future>
#include <thread>


template<typename Func, typename ...Args>
auto my_async(Func f, Args... args) { 
	std::packaged_task pt{f};
	std::future fi = pt.get_future();
	// need to move packaged_task and args into lambda context...otherwise they will
	// be destructed when the scope of my_async closes (i.e., we can't pass the arguments reference
	// since the original packaged_task will be garbage collected when the scope closes, and we
	// don't want to work with a copy of the pacakged_task, so we need to move it)
	std::thread([pt = std::move(pt), ... args = std::forward<Args>(args)]() mutable {
		pt(args...); 
	}).detach();
	return fi;
}

#endif

// MAIN.CPP
// #include <iostream>
// #include <chrono>
// #include <thread>
// #include "async.h"
// using namespace std::chrono_literals;

// int add(int x, int y) {
// 	std::this_thread::sleep_for(3s); // sleep for 3 seconds
// 	return x + y;
// }

// int main() {
// 	std::cout << "executing async func..." << std::endl;
// 	auto ft = my_async(add, 1, 1);
// 	std::cout << "waiting for async to finish and store result in future..." << std::endl;
// 	std::cout << ft.get() << std::endl;
// }
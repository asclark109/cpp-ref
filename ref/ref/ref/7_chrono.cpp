//////////////////
// std::chrono 
//////////////////
#include <chrono>

void exChrono(){
    std::chrono::system_clock::now(); // now – the current time
    std::chrono::system_clock::time_point; // type – what type of value represents the time (unsigned, long, etc)
    std::chrono::system_clock::period;    // If std::chrono::system_clock::period is std::ratio<1, 100>,
                                        // it ticks 100 times per second
    std::chrono::system_clock::is_steady; // accuracy – Is the tick period consistent or is it an average
}

////////////////////////////
// std::chrono – durations
////////////////////////////

void exChrono(){
    // std::chrono::seconds(std::chrono::days(1)).count();
    // sleep(std::chrono::milliseconds(30)); // yuck
}

////////////////////////////
// std::chrono – time points
////////////////////////////
// ⚫ Points in time associated with a clock
// ⚫ You can add or subtract a duration from a
// time point to get a new time point
// ⚫ You can subtract one time point from another
// to get a duration provided the time points
// came from the same clock
// ⚫ To get the current time_point, use std::chrono::system_clock::now();
#include<thread>
using namespace std::chrono_literals;

int add(int x, int y) {
	std::this_thread::sleep_for(5s);
	return x + y;
}

// #include<chrono>
// auto start = std::chrono::high_resolution_clock::now();
// auto end = std::chrono::high_resolution_clock::now();
// cout << "Elapsed time is " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
#include<chrono>
#include<thread>
using namespace std::chrono_literals;

int add(int x, int y) {
	std::this_thread::sleep_for(5s);
	return x + y;
}

// What does a temperature of 7 mean?
// ⚫ Fahrenheit, Celsius, Kelvin?
// ⚫ Let’s write a temperature class
// struct Temp { double degrees_K; };

// constexpr Temp operator"" _K(double d){ 
// 	return Temp{d}; 
// };

// constexpr Temp operator"" _C(double d){ 
// 	return Temp{d + 273.15 }; 
// };

// constexpr Temp operator"" _F(double d){ 
// 	return Temp{(d - 32)*5/9 + 273.15}; 
// };

// static_assert(32_F == 0_C); // Units clear

// Note: You can only write UDLs that begin with an
// underscore. Ones that don’t are reserved for the standard
// library
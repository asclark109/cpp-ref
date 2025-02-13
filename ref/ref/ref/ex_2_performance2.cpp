#include<chrono>
#include<iostream>
// #include<format>
using namespace std;
using namespace std::chrono;

class A {
public:
     int f(double i1, int i2) {
        return static_cast<int>(i1 * log(i1)) * i2;
    }
};

int main()
{
    auto a = make_unique<A>();
    int ai = 0;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 100'000'000; i++) {
        ai += a->f(10, i);
    }
    auto end = high_resolution_clock::now();
    // cout << format("result of {} took {:%Q%q}\n", ai, duration_cast<milliseconds>(end - start));
    return 0;
}

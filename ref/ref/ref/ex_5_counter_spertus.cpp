////////////
// SPERTUS
////////////
#include <utility>
#include <iostream>
// #include <format>
using namespace std;

template<typename Callable>
class Counter {
public:
  Counter(Callable t) : callable(t) {}
  template<typename ...Ts>
  auto operator()(Ts&& ...ts) {
    count++;
    return callable(forward<Ts>(ts)...);
  }
  unsigned count{};
private:
  Callable callable;
};

int f(double d)
{
  return static_cast<int>(2 * d);
}

Counter cf(f);

int main()
{
  cf(1.3); cf(2.4);
//   cout << format("f was called {} times\n", cf.count);
}

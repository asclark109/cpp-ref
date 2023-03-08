#include <concepts>
#include <iostream>
// #include <utility> ? std::forward

////////////////////////
// PERFECT FORWARDING
////////////////////////
// A lot of times you want to wrap a function and pass your arguments to it
// This is surprisingly difficult because you have to properly forward all
// the different ways of passing parameters
// e.g. lvalue references vs rvalue references

// e.g. attempt to implement make_unique
// first stab
template<class T>
struct unique_ptr{};

// makeUnique1: create object of type T, return unique_ptr to it. 
// assumes only 1 arg needed
template<typename T, typename Arg>
unique_ptr<T> makeUnique1(Arg arg) {
    return unique_ptr<T>(new T(arg));
}
// PROBLEM: assumes that T takes one constructor argument
// SOLUTION: VARIADICS
// C++ lets you use ... to indicate a “pack” of template parameters
// -- While there are a lot of details, the basic use is straightforward

// makeUnique2: create object of type T, return unique_ptr to it.
// can take any number of args.
template<typename T, typename... Arg>
unique_ptr<T> makeUnique2(Arg... arg) {
    return unique_ptr<T>(new T(arg...));
}
// PROBLEM: what is it?
struct X {
    // This constructor modifies its argument
    X(int &i) { i++; }
};
// if we were to do
int i{3};
unique_ptr<X> ptr = makeUnique2<X>(i);
// makeUnique2() receives i by Lvalue, meaning it gets a copy of i
// then X is constructed and modifies i...but this is modifying the
// local copy of i and not the original!
// PROBLEM: makeUnique infers that Args... is int, so i is passed by value.
// SOLUTION (TEMP): take arguments by reference

// makeUnique3: create object of type T, return unique_ptr to it.
// can take any number of L value args by reference.
template<typename T, typename... Arg>
unique_ptr<T> makeUnique3(Arg &... arg) {
    return unique_ptr<T>(new T(arg...));
}
// PROBLEM: can't bind a T& to an rvalue (only T&& binds to an Rvalue)
// make_unique3 with any rvalue arguments will give a compile error
// e.g.
// https://stackoverflow.com/questions/41322023/c-why-can-you-pass-rvalue-to-a-function-which-takes-lvalue-reference-as-argum
struct Y {
    Y(int i) { }
};

Y localVar{3}; // legal; 
int i{2};
Y localVar{i}; // legal;

unique_ptr<Y> ptr = makeUnique3<Y>(i); // legal: accepts the Lvalue by reference
// unique_ptr<Y> ptr = makeUnique3<Y>(3); // illegal!: only accepts Lvalues.
// cant accept Rvalues.

////////////////////////////////
// PERFECT-FORWARDING PROBLEM
////////////////////////////////
// want to pass arguments as-is to another function using that function’s signature

//////////////////////////////////////////////////////////
// std::foward does this
//////////////////////////////////////////////////////////
template<typename T, typename... Args>
unique_ptr<T> makeUnique(Args &&... args) {
    return unique_ptr<T>(new T(forward<Args>(args)...));
}
//////////////////////////////////////////////////////////

// (AUSTIN IMPL)
// implement a counter functor that accepts a function
// overloads the operator(), and can invoke the function it's
// been given. when it does, increment a counter
template<typename F>
class Counter1 {

    F myFunc;
    bool shouldCount{ true }; // can be used to toggle on-off the counting

public:
    Counter(F myFunc) {
        this->myFunc = myFunc;
    }
    int count{ 0 };

    template<typename ... Args>
    requires std::invocable<F&, Args ...>
    auto operator()(Args &&... args) {
        if (shouldCount)
            count++;
        return myFunc(std::forward<Args>(args)...);
    }

    void toggleCounting() {
        shouldCount = !shouldCount;
    }
};

// SPERTUS
template<typename Callable>
class Counter2 {
public:
  Counter(Callable t) : callable(t) {}
  
  template<typename ...Ts>
  auto operator()(Ts&& ...ts) {
    count++;
    return callable(std::forward<Ts>(ts)...);
  }
  unsigned count{};
private:
  Callable callable;
};

// SPERTUS: clever wrapping, unwrapping
template<typename T>
class Counter3 {
public:
  Counter(std::string name, T t) : name(name), t(t) {}
  template<typename ...Ts>
  auto operator()(Ts&& ...ts) {
    count++;
    return t(forward<Ts>(ts)...);
  }
  ~Counter() {
    cout << format("{} was called {} times\n", name, count);
  }
  unsigned count{};
private:
  std::string name;
  T t;
};

int f_impl(double d)
{
  return static_cast<int>(2 * d);
}

// int main()
// {
//     auto f = f_impl; // Uncomment for unwrapped
//     auto f = Counter3("f", f_impl); // Uncomment for wrapped
//     f(1.3); f(2.4);
// }




// EXAMPLE
#include <thread>
// How would I write jthread if I don't have it yet
// All it really needs is a joining destructor
struct MyJthread : public std::thread {
    template<typename Callable, typename ...Args>
    MyJthread(Callable&& c, Args&& ...args) 
      : thread(forward<Callable>(c), forward<Args>(args)...) {
    }
    ~MyJthread() { join(); }
};

struct MyJthread2 : public std::thread {
    using thread::thread; // Inherit constructors
    ~MyJthread2() { join(); }
};
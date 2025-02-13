////////////////////////////
// POINTERS TO FUNCTIONS
////////////////////////////
// The basic idea is usually that you describe a type by how it is used
int *ip;               // Means *ip is an int
int (*fp)(int, int);   // *fp can be called with 2 ints

int f(int i,int j) { /**/ }

void exFuncPtr(){
    // example    
    fp = &f;     // fp is type "int (*)(int, int)"
    fp(2, 3);
    // The following line only works without captures
    fp = [](int i, int j) { return i + j; };   // also type "int (*)(int, int)"
}

////////////////////////////
// WHY FUNCTION POINTERS??
////////////////////////////

////////////////////////////////////////////////////////////
// WHEN YOU DONT KNOW WHAT THE FUNCTION WILL BE AT RUNTIME
////////////////////////////////////////////////////////////
// Sometimes we don’t know what function we want to call until runtime
#include <iostream>
#include <string>
#include <vector>

std::vector<double> getHomePrices(){
    std::vector<double> nums{1,2,3};
    return nums;
};

double mean(std::vector<double> const &) { /**/}
double median(std::vector<double> const &) { /**/ }

void exFuncPtr2(){
    std::cout << "Should I use means or medians ";
    std::string answer;
    std::cin >> answer; // e.g. "mean" "median"
    double (*averager)(std::vector<double> const &) = (answer == "mean" ? mean : median); // function ptr "averager" is a ptr to a func that accepts a vector of doubles, returns double
    std::cout << "The average home price is ";
    std::cout << averager(getHomePrices()) << std::endl;
}

//////////////////////////
// POINTERS TO MEMBERS
//////////////////////////
// Pointers to members
struct B {
    int i;
    int j;
    void foo(double){};
    void bar(double){};
};
// We would like to be able to point to a particular member of A
// Not an address because we haven’t specified an A object
// More like an offset into A objects
void ExFuncPtr3(){
    int B::*aip = &B::i;                // struct member variable pointer: given a pointer to A will return the i member
    void (B::*afp)(double) = &B::foo;   // struct member function pointer: given a pointer to A will invoke A.function(double)
    B *ap = new B;                      // ap == ptr to an A
    B a;                                // a  == instance of A
    ap->*aip = 3;                       // Set ap->i to 3
    (a.*afp)(3.141592);                 // Calls a.foo(3.141592)
}

//////////////////////////
// POINTERS TO MEMBER FUNCTIONS
//////////////////////////
struct Animal{
    void eat();
    void sleep();
};

void exPtrFuncMember() {
    std::vector<Animal*> zoo;
    Animal elephant{};
    zoo.push_back(&elephant);
    // zoo.push_back(new Elephant);
    // zoo.push_back(new Zebra);
    // zoo.push_back(new Bear);
    std::cout << "Feeding time (f) or Bedtime (b)?";
    char c;
    std::cin >> c;

    void (Animal::*ap)() = c == 'f' ? &Animal::eat : &Animal::sleep;  // POINTER TO MEMBER FUNCTION
    for(auto animal : zoo) {
        // animal->(*ap)();
    }
}

// EXAMPLE (WITH SMART POINTERS)
void exPtrFuncMemberSmart() {
    std::vector<std::unique_ptr<Animal>> zoo;
    Animal elephant{};
    // zoo.emplace_back(new Elephant);
    // zoo.emplace_back(new Zebra);
    // zoo.emplace_back(new Bear);
    std::cout << "Feeding time (f) or Bedtime (b)?";
    char c;
    std::cin >> c;
    void (Animal::*ap)()
    = c == 'f' ? &Animal::eat : &Animal::sleep;
    for (auto it = zoo.begin(); it != zoo.end(); it++) {
        ((**it).*ap)();
    }
}

//////////////////////////
// CANT ASSIGN FUNCTOR TO FUNCTION POINTER
//////////////////////////

//////////////////////////
// CAN ONLY ASSIGN LAMBDAS WITH NO CAPTURE LIST TO POINTER
//////////////////////////

//////////////////////////////////////
// STD::FUNCTION std::function
//////////////////////////////////////
// We have just discussed function pointers, but
// in C++, functions aren’t the only thing that
// can be called
// ⚫ Call a function
// ⚫ Call a lambda
// ⚫ Call a functor
// ⚫ Call a member function
// std::function CAN HOLD ANYTHING CALLABLE

// EXAMPLE: STD::FUNCTION HOLDING LAMBDAS
#include <functional>
#include <numeric>
#include <iostream>

struct WeightedMean {
    WeightedMean(std::vector<double> const &weights): weights(weights) {
    }

    double operator()(std::vector<double> const & data) {
        return inner_product(data.begin(), data.end(), weights.begin(), 0.0)
            / accumulate(weights.begin(), weights.end(), 0.0);
    }
    
    std::vector<double> weights;
};

std::function<double(std::vector<double> const &)> averager = WeightedMean({1.5, 3.6, 4.2}); // OK. put a functor into a std::function
// std::cout << "The average home price is ";
// std::cout << averager(getHomePrices()) << std::endl;

// EXAMPLE: STD::FUNCTION HOLDING MEMBER POINTER
struct A {
    int i;
};

void exStdFunction(){
    std::function<int(A*)> fp = &A::i; // std::function receives a member pointer
    A a;
    fp(&a);
}

////////////////////////////////////////////////////////////
// OFTEN YOU CAN CHOOSE BETEEN STD::FUNCTION AND A TEMPLATE
////////////////////////////////////////////////////////////
// Often you can choose between a std::function and a template
// In the below code, tmpl_apply and fn_apply can be used similarly

template<typename Callable>
double tmpl_apply(Callable c, std::vector<double> const &data) {
    return c(data);
};

double fn_apply(std::function<double(std::vector<double> const &)> c, std::vector<double> const & data) {
    return c(data);
}

void f() {
    tmpl_apply(mean, {1.7, 2.3}); // OK
    fn_apply(mean, {1.7, 2.3}); // OK
    tmpl_apply(WeightedMean({1.2, 3.4}), {1.7, 2.3}); // OK
    fn_apply(WeightedMean({1.2, 3.4}), {1.7, 2.3}); // OK
}
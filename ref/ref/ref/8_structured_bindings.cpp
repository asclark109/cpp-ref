//////////////////////////
// STRUCTURED BINDINGS
//////////////////////////
// works well with functions of multiple return values

// originally, used std::tie to map multiple return
// values of a function into variables, but it was 
// awkward.

// It can only assign to existing variables
// It doesn't deduce types
// It can't decompose types other than tuple/pair
#include <tuple>
#include <string>
using std::tuple;
using std::string;
using std::tie;

struct Person{};
struct Rank{};

void exTie(){
    Person Mike{};
    tuple<string, Rank, long> identity(Person);
    string name;
    Rank rank;
    tie(name, rank, std::ignore) = identity(Mike); // AWKWARD
}

////////////////////////
// STRUCTURED BINDINGS
////////////////////////
// structured bindings (C++17) solve this.
void exStructuredBindings() {
    // EX 1
    int a[2] = {1,2};
    auto [x,y] = a; // creates temp e[2], copies a into e, then x refers to e[0], y refers to e[1]
    auto& [xr, yr] = a; // xr refers to a[0], yr refers to a[1]
    
    // EX 2
    float x1{}; char y1{}; int z1{};
    tuple<float&,char&&,int> tpl(x1,std::move(y1),z1);
    const auto& [a,b,c] = tpl;
    // a names a structured binding of type float& that refers to x
    // b names a structured binding of type char&& that refers to y
    // c names a structured binding of type const int that refers to the 3rd element of tpl

    // EX 3
    struct S {
        int x1 : 2;
        volatile double y1; 
    };

    S f{};
    auto const [x, y] = f; 
    // x is a const int lvalue identifying the 2-bit bit field
    // y is a const volatile double lvalue
}

////////////////////////////
// EXAMPLE:
////////////////////////////
#include <memory>
#include <iostream>
#include <utility>
using std::unique_ptr;
using std::cout;
using std::pair;
using std::make_unique;

struct Page{};
// void processPage(Page p);
void processPage(unique_ptr<Page> p);

// Suppose we have a function that returns either a web page
// or a network error code
pair<unique_ptr<Page>, int> getWebPage() {
    /* … */
    unique_ptr page = make_unique<Page>();
    auto errCode = 200;
    auto succeeded = true;
    if(succeeded)
        return { move(page), 0 };
    else
        return { move(page), errCode };
};

void exRealistic(){    
    /* ... */
    auto [ page, err] = getWebPage();
    if(!err) processPage(move(page));
    else if (err == 404) { cout << "Not found" << std::endl; }
    // else { cout << format("Unknown error {}\n“, err); }   
}
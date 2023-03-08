//////////////
// SHARED PTR
//////////////
// make_shared and make_unique
// make_shared<T> and make_unique<T> create an object
// and return an owning pointer

//////////////
// CREATION
//////////////
// The following two lines act the same
#include <memory>
struct A{};
auto ap = std::make_shared<A>(4, 7);     // CREATION
// std::shared_ptr<A> ap = new A(4, 7);

//////////////
// RELEASE
//////////////
void f() {
    ap.reset();  // shared_ptr releases ownership (don't use ap anymore)
}

// example
void f() {
    auto a1 = std::make_unique<A>();
    auto a2 = std::make_unique<A>();
    // g(A *, A *) is responsible for deleting
    // g(a1.reset(), a2.reset()); // reset releases ownership (from the shared_ptr)
}

////////////////////////////////////////////////////    
// USE UNIQUE_PTR, SHARED_PTR OVER DIRECT USE OF NEW
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// GET RAW POINTER FROM SMART POINTER
////////////////////////////////////////////////////
auto a = ap.get();


// SEE PROMISES AND FUTURES EXAMPLE IMPL
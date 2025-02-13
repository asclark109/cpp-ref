// STATIC POLYMORPHISM
// Used to be very common because people wanted to
// produce high performance code that "looks like" inheritance
// and overriding "OO"
// ⚫ "Traditional OO is better"
// ⚫ Now less common
// ⚫ Lots of boilerplate
// ⚫ Disadvantages of templates (no runtime dispatch)
// ⚫ Disadvantages of OO (having to inherit is a headache)
#include<string>
#include<memory>
#include<iostream>
#include<string>
using namespace std;

template<typename T>
struct Animal {
	string name() const { return static_cast<T const *>(this)->name(); }
	string eats() const { return static_cast<T const&>(*this).eats(); } // If you'd rather not have a raw point
};

struct Cat : public Animal<Cat> {
	string name() const { return "cat"; }
	string eats() const { return "mice"; }
};

struct Dog : public Animal<Dog> {
	string name() const { return "dog"; }
	string eats() const { return "cats"; }
};

int lifespan(Animal<Cat> const &) { return 12; }
int lifespan(Animal<Dog> const &) { return 10; }

template<typename T>
void do_stuff(Animal<T> const &a) {
	cout << "A " << a.name() << " eats " << a.eats();
    cout << " and lives " << lifespan(a) << " years";
};

int main() {
    do_stuff(Cat());
}

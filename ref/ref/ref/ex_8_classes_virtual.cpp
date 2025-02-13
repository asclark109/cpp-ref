// Create and extend classes with OO

// Full runtime-dispatch
// ⚫ Must inherit
// ⚫ Very safe "nominal" typing
// ⚫ But can result in hard to maintain "spaghetti inheritance"
// ⚫ Objects expensive to create with make_unique

#include<string>
#include<memory>
#include<iostream>
using namespace std;
class Cat;
class Dog;

struct AnimalVisitor {
    virtual void visit(Cat &) const = 0;
    virtual void visit(Dog &) const = 0;
};

struct Animal {
    virtual string name() = 0;
    virtual string eats() = 0;
    virtual void accept(AnimalVisitor const &v) = 0;
};

class Cat : public Animal {
    string name() override { return "cat"; }
    string eats() override { return "delicious mice"; }
    virtual void accept(AnimalVisitor const &v) { v.visit(*this); }
};

class Dog : public Animal {
    string name() override { return "dog"; }
    string eats() override { return "delicious cats"; }
    virtual void accept(AnimalVisitor const &v) { v.visit(*this); }
};

struct LifeSpanVisitor : public AnimalVisitor
{
    LifeSpanVisitor(int &i) : i(i) {} 
    void visit(Dog &) const { i = 10; } 
    void visit(Cat &) const { i = 12; } 
    int &i;
};

int main() 
{
    unique_ptr<Animal> a = make_unique<Cat>();
    cout << "A " << a->name() << " eats " << a->eats() << endl;
    int years;
    a->accept(LifeSpanVisitor(years));
    cout << "It lives " << years << " years\n";
}

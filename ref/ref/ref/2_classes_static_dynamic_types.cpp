#ifndef EXCLASSES_STATIC_DYNAMIC_TYPES_H
#  define EXCLASSES_STATIC_DYNAMIC_TYPES_H

#include<string>
#include<iostream>
#include<vector>

struct Animal { /* ... */ };
class Gorilla : public Animal {/* ... */ };
class Falcon : public Animal {/* ... */ };
// This means that a Gorilla “isA” Animal and can be referred to by Animal references

void exCLASSES_STATIC_DYNAMIC_TYPES() {
    // The STATIC TYPE is the type of the expression (Known at compile time)
    // The DYNAMIC TYPE is the type of the actual object referred to by the expression (May be knowable only at run-time)
    
    // Static and dynamic type generally only differ due to inheritance
    int i = 5;     // S = int,     D = int
    Gorilla g;     // S = Gorilla, D = Gorilla
    Animal &a = g; // S = An&,     D = Gorilla
    Animal a2 = g; // Oops! Can’t copy a Gorilla into an Animal

    std::unique_ptr<Animal> ua = std::make_unique<Gorilla>();
    // Static type of *ua is Animal
    // Dynamic type is Gorilla

    ua = std::make_unique<Falcon>();
    // now:
    // Static type of *ua is Animal
    // Dynamic type is Gorilla
}

#endif
#ifndef EXCLASS_MEMBERS_CONSTRUCTOR_H
#  define EXCLASS_MEMBERS_CONSTRUCTOR_H

// Classes have “destructor” methods that do
// any needed cleanup when the object goes
// away. When an object in memory goes away, its
// destructor is always called

struct A {
    ~A() {
        /* Code to cleanup resources used by A */
    }
};

//////////////////
// DESTRUCTOR (Implicitly-generated)
//////////////////

// If you don’t write one, the compiler will generate
// it for you, called the default destructor
//  This will simply destroy all of the fields and base
// classes in the reverse of the order we gave for
// constructing them

// VIRTUAL DESTRUCTORS
// unique_ptr<Animal> is managing dynamic type Gorilla at runtime
// if Animal's destructor is not virtual, Animal's destructor is called

////////////////////////////////////////////////////
// BEST PRACTICES: Classes that are meant to be
// inherited from should have a virtual destructor
////////////////////////////////////////////////////

#endif
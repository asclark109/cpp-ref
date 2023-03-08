//////////
// SOLID
//////////
// Single Responsibility Principle
// Open-Closed Principle
// Liskov Substitution Principle
// Interface Segregation
// Dependency Inverison

//////////////////////////////////
// SINGLE RESPONSIBLITY PRINCIPLE
//////////////////////////////////
// (1) decompose classes to be single purpose
//     -- e.g. if it has logical groupings of methods and data, pushdown them into classes
// (2) decompose functions to be single purpose (some are too big)
//     (2a) if the functions need more state, use functors (good choice for complex functions)
//     (2b) create more smaller functions.
//     (3b) use lambdas with capture list 
//              Good for "goldilocks" cases where a class is overkill but
//              multiple responsibilities risk a "spaghetti" function

//////////////////////////////////
// OPEN/CLOSED PRINCIPLE
// software constructs should be:
// (1) Open for extension (Allows the addition of new capabilities over time)
// (2) Closed for modification (Don't break existing client code)
//////////////////////////////////
// How to achieve "open for extension"?
// (1) INHERITANCE AND VIRTUAL FUNCTIONS are a great way to extend classes
//    -- doesn't cover extremely common use cases for extensions though
//    PROBLEM: CLIENT-SIDE EXTENSION
//      -- Suppose you are using a class hierarchy, and you wish
//      the classes had a virtual method specific to the needs of
//      your application
//      -- Unfortunately, it probably doesn't because the class
//      designer doesn’t understand your application
//          -- You may not be able to add them
//          -- Maybe they’re not your classes
//          -- Maybe the virtuals you want only apply to your particular
//             program, and it breaks encapsulation to clutter up a general
//             interface with the particulars of every app that uses them
// (2) VISITOR PATTERN

//////////////////////
// VISITOR PATTERN
//////////////////////
// The Visitor Pattern is a way to make your class hierarchies extensible
// -- Suppose, as a user of the Animal class, I wished that it had a lifespan() method,
//    but the class designer did not provide one
// (0) create a visitor class that can be extended. AnimalVisitor base class (pure virtual functions)
// (1) add an accept method to each class in the class hierarchy. // Animal::accept(AnimalVisitor av);
// (2) create a visitor subclass that implements the methods you wish were there

//////////////////////////////////////////////////////
// BEST PRACTICE
// If you are designing a class hierarchy where the
// best interface is unclear, add an accept()
// method as a customization point
//////////////////////////////////////////////////////

// EXAMPLE
struct Animal {
    /* ... */
};
struct Cat : public Animal {
    /* ... */
};
struct Dog : public Animal {
    /* ... */
};

// (0)
struct AnimalVisitor {
    virtual void visit(Cat &) const = 0;
    virtual void visit(Dog &) const = 0;
};

// (1)
struct Animal {
    /* ... */
    virtual void accept(AnimalVisitor const & av) = 0;
};
struct Cat : public Animal {
    /* ... */
    virtual void accept(AnimalVisitor const & av){
        av.visit(*this); 
    };
};
struct Dog : public Animal {
    /* ... */
    virtual void accept(AnimalVisitor const & av){
        av.visit(*this); 
    };
};

// (2)
struct LifeSpanVisitor : public AnimalVisitor {
    LifeSpanVisitor(int &i) : i(i) {}
    void visit(Cat &) const { i = 10; };
    void visit(Dog &) const { i = 13; };
    int &i;
};

#include <iostream>
#include <memory>
using std::make_unique;
using std::unique_ptr;

void exUseVisitor(){
    int years{10};
    unique_ptr<Animal> a = make_unique<Cat>();
    a->accept(LifeSpanVisitor(years));
    std::cout << "lives " << years;
}

//////////////////////////
// LISKOV SUBSTITUTION
//////////////////////////
// (1) Inheritance (CLASSES, VIRTUAL FUNCTIONS) is one way of modeling subtyping
// (2) Concepts (e.g. if Animal is a concept instead of base class)
//          other benefit of concepts is that
//          inheritance only inherits methods, but
//          concepts can specify almost arbitrary Φ (x)
//          properties
// TRADEOFF: EFFICIENCY vs DYNAMISM

////////////////////////////////////
// INTERFACE SEGREGATION PRINCIPLE
// No code should be forced to depend on methods it doesn't use
////////////////////////////////////
// (Martin) Suppose we have a fat "Job" class
// that has a bunch of methods that are only
// relevant to print jobs and other methods that
// are only relevant to stapling jobs
//
// If the stapling code takes a Job, it will
// needlessly only work with Jobs that also
// know about printing
//
// This is often given as a motivation for using
// (1) ABSTRACT BASE CLASSES (MULTIPLE INTERFACES)
// -- The concrete Job class implements the PrintJob and StapleJob interfaces
// -- This can be taken so far, getting into spaghetti inheritance and 
//    excessive multiple inheritance complexity
// (2) CONCEPTS also handle this nicely
// -- The stapling code can only require what it
//    needs to staple without exploding the type
//    hierarchy
// -- However, you could also go too far with this
//    too as an incoherent set of functions that
//    each make different requirements of each job
//    that is passed in
// -- Both of these are good reminders that
//    architecture is more art than science

////////////////////////////////////
// DEPENDENCY INVERSION PRINCIPLE
////////////////////////////////////
// This is sometimes paraphrased as "All
// programming problems can be solved with an
// extra layer of indirection"
//
// “the most flexible systems are those in which
// source code dependencies refer only to
// abstractions, not to concretions”
//
// Suppose you have a thumbnail service class that
// looks for pictures in S3 folders
struct S3Folder {};
class ThumbnailService1 {
    S3Folder inputFolder;
    /**/
};
// It is now coupled with the concrete S3 service
// instead of an abstract idea of a storage service,
// which is probably sufficient for this use
//
// -- Again, the indirection can be introduced either
// through inheritance/virtuals or template/concepts
//
// Usual performance/dynamism tradeoff

// (1) SOLVING WITH INHERITANCE AND VIRTUALS
class Folder{};
class S3Folder : public Folder { /**/ };

class ThumbnailService2 {
    ThumbnailService2(Folder &inputFolder)
        : inputFolder(inputFolder) {};

    Folder &inputFolder;
};

// (2) SOLVING WITH TEMPLATES AND CONCEPTS
#include <concepts>
using std::convertible_to;

#include <string>
using std::string;

// Create the concept
template<typename T>
concept FolderConcept = requires(T a) {
    { a.pages() } -> convertible_to<int>;
};

// Create a template using the concept
template<FolderConcept F> // FolderConcept is a concept
struct ThumbnailService3 {
    FolderConcept &inputFolder;
    /* ... */
};

struct S3Folder2{
    int pages(){return 1;};
};

void exTemplatesAndConcepts(){
    // ThumbnailService3<S3Folder2> ts;
    // S3Folder2 myS3Folder{};
    // ThumbnailService3 ts2(myS3Folder); // CTAD
}

//////////////////////////
// OPTIONAL  std::optional
//////////////////////////
// Sometimes it is useful for an object to be unset
// ⚫ E.g., like null in Java or None in Python
// ⚫ If you know about pointers, they can be null as well

#include <optional>
#include <iostream>
using std::optional;
using std::cout;
using std::endl;

// f may fail or return an int
// optional<int> f(bool x) { 
//     return x? 1 : {};
// }

// void exOptional() {
//     auto r = f(true);
//     if(r) { // f return a result
//         cout << "succeeded: " << r.value() << endl;
//     } else {
//         cout << "failed" << endl;
//     }
// }

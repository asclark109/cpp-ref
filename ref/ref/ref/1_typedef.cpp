#ifndef EXTYPEDEF_H
#  define EXTYPEDEF_H

#include <vector>
#include <iostream>

typedef std::vector<int> Row;  // old-fashioned; DONT DO IT; creates a type alias for vector<int> to be used henceforth
using Triangle = std::vector<Row>; // better, Alternate notation for typedef

void exTYPEDEF() {
    /*
    Typedef: reserved keyword used to create an additional name (alias)
    for another data type. It is a new identifier for an existing type,
    and it helps with readability and reducing typos. Like a nickname

    you might have a really long data type like 
        std::vector<std::pair<std::string,int>>
    and you want to create an alias for it so it is easier to reference.

    it is common to end the new alias name with _t
	*/
    typedef std::vector<std::pair<std::string,int>> pairlist_t;
    typedef std::string text_t;
    typedef int number_t;

    text_t firstName = "bro"; // behaves exactly like a string
    number_t age = 21; // behaves exactly like a string

    // BETTER
    // Instead of using typedef, it is recommended to use the using keyword
    // this is because it is more suitable for use in templates (later)
    using pairlist_t = std::vector<std::pair<std::string,int>>;
    using text_t = std::string;
    using number_t = int;
	
}

#endif
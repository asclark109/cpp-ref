#ifndef EXUSING_H
#  define EXUSING_H

#include <vector>
#include <iostream>

//////////////////////////////////////////
// (2) using (BEST)
//////////////////////////////////////////
using Row      = std::vector<int>;
using Triangle = std::vector<Row>; // BETTER, Alternate notation for typedef

void exUSING() {
    ////////////////////
    // CREATE using
    ////////////////////
    // Instead of using typedef, it is recommended to use the using keyword
    // this is because it is more SUITABLE FOR USE IN TEMPLATES.
    using pairlist_t = std::vector<std::pair<std::string,int>>;
    using text_t = std::string;
    using number_t = int;
	
    text_t firstName = "bro"; // behaves exactly like a string
    number_t age = 21; // behaves exactly like a string
}

#endif
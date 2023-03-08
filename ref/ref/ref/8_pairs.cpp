//////////
// PAIRS
//////////
// Pairs are like tuples that always have two types

// One natural use for pair and tuple is to let
// functions return multiple values
#include <utility>
using std::pair;

pair<int, int> f() {
    return {1, 2}; // ok
}

// Only difference is members also have name
// p.first is effectively a synonym for get<0>(p)
// p.second is effectively a synonym for get<1>(p)
//  Note that get is zero-based (as it should be) while the field names starts at one

void exPair(){
    auto p = f();
    p.first;  // same as get<0>(p);
    p.second; // same as get<1>(p);
    get<0>(p);
    get<1>(p);
}

//////////////////////////////////////////////////
// PAIRS ARE USED IN THE MAPS AS A KEY-VALUE PAIR
//////////////////////////////////////////////////
#include <map>
#include <string>
#include <iostream>
using std::map;
using std::string;
using std::cout;

void exMap(){
    map<int, string> m = {
        {1, "foo"},
        {0, "bar"}
    };

    for (auto &kv: m) { // kv is a pair<int, string>
        kv.first;   // key
        kv.second;  // value
    }
}
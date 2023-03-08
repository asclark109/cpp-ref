#include <iostream>
#include <vector>
#include <numeric>       // accumulate
using std::accumulate;

namespace numeric_accumulate {

    double square(double x) {
        return pow(x, 2);
    }

    void exACCUMULATE() {
        std::vector<double> vNums { 1.0, 2.0, 4.5, 3.0, 5.0 }; 

        // COMPUTES THE SUM OF THE GIVEN VALUE init AND THE ELEMENTS IN THE RANGE [first, last)
        auto sqrdDist = std::accumulate(vNums.begin(), vNums.end(), 0.0);  // CTAD!

    }

}


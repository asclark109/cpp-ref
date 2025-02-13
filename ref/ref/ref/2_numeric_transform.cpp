#include <iostream>
#include <vector>
#include <algorithm>   // transform
using std::transform;

namespace numeric_transform {

    double square(double x) {
        return pow(x, 2);
    }

    void exTRANSFORM() {
        
        std::vector<double> vNums { 1.0, 2.0, 4.5, 3.0, 5.0 }; 
        std::vector<double> vSqrdNums;

        // APPLIES A FUNCTION TO A RANGE AND STORES THE RESULT IN ANOTHER RANGE,
        // keeping the original elements order and beginning at vNum.begin()
        vSqrdNums.resize(vNums.size()); // create space to copy elems into vSqrd
        transform(vNums.begin(), vNums.end(), vSqrdNums.begin(), square);
          
    }
}


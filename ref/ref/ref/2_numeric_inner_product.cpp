#include <iostream>
#include <vector>
#include <numeric>   // inner_product
using std::inner_product;

namespace numeric_innerproduct {

    double square(double x) {
        return pow(x, 2);
    }

    void exINNERPRODUCT() {
        
        std::vector<double> vNums { 1.0, 2.0, 4.5, 3.0, 5.0 }; 
        std::vector<double> vSqrdNums;

        // COMPUTES INNER PRODUCT (SUM OF PRODUCTS) OR PERFORMS ORDERED MAP/REDUCE OPERATION
        // ON THE RANGE [first1, last1) AND THE RANGE BEGINNING AT first2.
        // (i.e. squares each elem and adds them together)
        auto dist = sqrt(inner_product(vNums.begin(), vNums.end(), vNums.begin(), 0.0));

        
    }



}


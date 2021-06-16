#include <iostream>
#include "matrix.hpp"
#include "pair.hpp"
using namespace std;


int main()
{
    Matrix m1({{1,2},{4,4}}),  m2(4,5);
    PairOfMatrices p1 {m1, std::move(m2)};
    // PairOfMatrices p2 = p1;   // ERROR!     | Yes
    PairOfMatrices p3 = std::move(p1);
    Matrix a = p3.left, b=p3.right;
    PairOfMatrices p4{a,b};
    // p1 = p4;  // ERROR!     | Yes
    p1 = std::move(p4);
    return 0;
}

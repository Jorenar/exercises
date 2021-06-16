#if __cpp_if_constexpr < 201606L
    #error You need C++17
#endif

#include <iostream>
#include "dotProduct.hpp"
#include "multiply.hpp"

int main()
{
    double a[] = { 1, 2, 3 };
    double b[] = { 1, 1, 1 };
    std::cout<< DotProduct<3>(a, b) << std::endl; // 6

    double x[] = { 1, 1, 0 };
    double A[] = { 1, 0, 0,
                   2, -5, 1 };
    double y[2] = { 0.0 };
    Multiply<2,3>(A, x, y);
    std::cout << y[0] << " " << y[1] << std::endl; // 1 -3

    return 0;
}

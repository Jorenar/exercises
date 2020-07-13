#include <iostream>
#include "power.hpp"
#include "binomial.hpp"

int main()
{
    std::cout << Power<5,3>::value      << std::endl; // 125
    std::cout << Binomial<4,2>::value   << std::endl; // 6
    std::cout << Binomial<100,0>::value << std::endl; // 1
    std::cout << Binomial<100,1>::value << std::endl; // 100
    std::cout << Binomial<100,7>::value << std::endl; // 16007560800
    return 0;
}

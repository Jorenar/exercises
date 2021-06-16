#include "ex_1_29.hpp"
#include <iostream>

int main()
{
    Ex_1_29<10> x;
    x.push(2);
    x.push(2);
    x.push(2);
    x.push(2);
    x.push(5);

    std::cout << x.pop() << std::endl;
    std::cout << x.pop() << std::endl;
    std::cout << x.pop() << std::endl;
    std::cout << x.pop() << std::endl;
    std::cout << x.pop() << std::endl;

    return 0;
}

#include <iostream>
#include "IntegerList.hpp"

int main()
{
    using listA = IntegerList<5, -1, 5, 2, 1>;
    using listB = IntegerList<1, 4, 6, 9>;
    std::cout << "List A : " << listA() << std::endl;
    std::cout << "List B : " << listB() << std::endl;

    // using listC = Join<listA, listB>::type;
    // std::cout << "List C : " << listC() << std::endl;

    // std::cout << boolalpha;
    // std::cout << "Is A sorted? " << IsSorted<listA>::value << std::endl;
    // std::cout << "Is B sorted? " << IsSorted<listB>::value << std::endl;

    // std::cout << Max<listC>::value << std::endl;
}

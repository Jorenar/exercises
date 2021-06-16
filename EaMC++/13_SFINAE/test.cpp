#include <iostream>
#include <vector>
#include <list>

#include "checkIfHas.hpp"
#include "enableIf.hpp"
#include "median.hpp"

int main()
{
    std::cout << "Zad 1:" << std::endl;
    {
        std::cout << "  " << hasSize_v<int>                    << "   (0)" << std::endl;
        std::cout << "  " << hasSize_v<std::vector<int> >      << "   (1)" << std::endl;
        std::cout << "  " << hasValueType_v<int>               << "   (0)" << std::endl;
        std::cout << "  " << hasValueType_v<std::vector<int> > << "   (1)" << std::endl;
    }

    std::cout << "Zad 2:" << std::endl;
    {
        std::vector<int> v{ 1,2,3,4,5 };
        std::cout << "  " << v1::getSize(5) << "   (4)" << std::endl;
        std::cout << "  " << v1::getSize(v) << "  (20)" << std::endl;
        std::cout << "  " << v2::getSize(5) << "   (4)" << std::endl;
        std::cout << "  " << v2::getSize(v) << "  (20)" << std::endl;
    }

    std::cout << "Zad 3:" << std::endl;
    {
        std::list<int> a{ 3, 2, 5, 1, 4 };
        std::cout << "  " << median(a) << "   (3)" << std::endl;
        std::list<int> b{ 3, 2, 1, 4 };
        std::cout << "  " << median(b) << " (2.5)" << std::endl;
        std::vector<int> w{ 3, 1, 5, 4, 2 };
        std::cout << "  " << median(w) << "   (3)" << std::endl;
        std::vector<int> v{ 3, 1, 4, 2 };
        std::cout << "  " << median(v) << " (2.5)" << std::endl;
        return 0;
    }
}

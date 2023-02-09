#include <fstream>
#include <iostream>

#include "Dict.hpp"

int main(int argc, char const* argv[])
{
    Dict<std::string, std::string> d;

    if (argc > 1) {
        std::ifstream file{ argv[1] };
        std::string in_l;
        std::string in_r;
        while (file >> in_l) {
            file >> in_r;
            d[in_l] = in_r;
        }
    }

    std::string in;
    while (std::cin >> in) {
        std::cout << (d.find(in) ? d[in] : "-") << "\n";
    }


#ifdef DEBUG
    d.buckets();
#endif

    return 0;
}

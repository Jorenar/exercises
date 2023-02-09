#include "Generator.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);

    genData<unsigned int> gen;

    auto n = argc > 1 ? std::stoull(argv[1]) : gen.dataSize();
    auto max = argc > 2 ? std::stoi(argv[2]) : gen.maxValue();

    for (const auto& x: gen(n,max))
    {
        std::cout << x << '\n';
    }

    return 0;
}

#include <vector>
#include <algorithm>
#include <random>

template<typename T>
class genData {
    std::mt19937 mt;

    using ud = std::uniform_int_distribution<T>;
    ud ud_size;
    ud ud_max;

public:
    genData() :
        mt{std::random_device{}()},
        ud_size(1,1e3),
        ud_max(1,1e6)
    {}

    T dataSize()
    {
        return this->ud_size(mt);
    }

    T maxValue()
    {
        return this->ud_max(mt);
    }

    std::vector<T> operator ()(std::size_t n, T max)
    {
        ud genVal(1, max);
        std::vector<T> V(n);
        std::generate(V.begin(), V.end(), [&]() { return genVal(mt); });
        return V;
    }

    std::vector<T> operator ()(std::size_t n)
    {
        return (*this)(n, maxValue());
    }

    std::vector<T> operator ()()
    {
        return (*this)(this->dataSize());
    }
};

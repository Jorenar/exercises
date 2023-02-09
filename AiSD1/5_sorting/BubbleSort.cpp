#include "main.cpp" // pain

#include <vector>

template<typename T>
int sort(std::vector<T>& vec)
{
    bool swapped;
    auto n = vec.size() - 1;
    for (std::size_t i = 0; i < n; ++i) {
        swapped = false;
        for (std::size_t j = 0; j < n-i; ++j) {
            if (vec[j] > vec[j+1]) {
                std::swap(vec[j], vec[j+1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }

    return 0;
}

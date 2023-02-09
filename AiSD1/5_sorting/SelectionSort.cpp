#include "main.cpp" // pain

#include <vector>

template<typename T>
int sort(std::vector<T>& vec)
{
    auto n = vec.size();

    for (std::size_t i = 0; i < n-1; ++i) {
        auto minIdx = i;
        for (std::size_t j = i+1; j < n; ++j) {
            if (vec[j] < vec[minIdx]) {
                minIdx = j;
            }
        }

        if (minIdx != i) {
            std::swap(vec[i], vec[minIdx]);
        }
    }

    return 0;
}

#include "main.cpp" // pain

#include <vector>

template<typename T>
int sort(std::vector<T>& v)
{
    auto n = v.size() - 1;
    for (std::size_t i = 0; i < n; ++i) {
        auto minIdx = i;
        auto maxIdx = i;
        auto max = v[i];

        for (std::size_t j = i; j <= n; ++j) {
            if (v[j] < v[minIdx]) {
                minIdx = j;
            }
            if (v[j] > v[maxIdx]) {
                maxIdx = j;
                max = v[j];
            }
        }

        std::swap(v[i], v[minIdx]);

        if (v[minIdx] == max) {
            std::swap(v[n], v[minIdx]);
        }
        else {
            std::swap(v[n], v[maxIdx]);
        }

        --n;
    }

    return 0;
}

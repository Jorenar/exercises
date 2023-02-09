#include "main.cpp" // pain

#include <algorithm>
#include <vector>

template<typename T>
int sort(std::vector<T>& vec)
{
    auto max = *std::max_element(vec.begin(), vec.end());
    auto min = *std::min_element(vec.begin(), vec.end());
    std::size_t range = max - min + 1;

    std::vector<T> count(range);
    std::vector<T> out(vec.size());

    for (const auto& v: vec) {
        ++count[v - min];
    }

    for (std::size_t i = 1; i < count.size(); ++i) {
        count[i] += count[i-1];
    }

    for (std::size_t i = vec.size() - 1; i-- > 0; /**/) {
        out[count[vec[i] - min] - 1] = vec[i];
        count[vec[i] - min]--;
    }

    vec = std::move(out);

    return 0;
}

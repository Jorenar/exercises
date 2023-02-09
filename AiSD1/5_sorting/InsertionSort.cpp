#include "main.cpp" // pain

#include <vector>

template<typename T>
int sort(std::vector<T>& vec)
{
    using signed_size_t = std::make_signed_t<std::size_t>;
    int domOper = 0;

    for (std::size_t i = 1; i < vec.size(); ++i) {
        auto temp = vec[i];
        signed_size_t j = i - 1;
        while (++domOper && j >= 0 && vec[j] > temp) {
            vec[j+1] = vec[j];
            --j;
        }
        vec[j+1] = temp;
    }

    return domOper;
}

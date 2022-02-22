#pragma once

#include <cstddef>

int rnd();

template<typename T>
bool isSorted(const T& arr)
{
    for (std::size_t i = 0; i < arr.size-1; ++i) {
        if (arr[i] > arr[i+1]) {
            return false;
        }
    }
    return true;
}

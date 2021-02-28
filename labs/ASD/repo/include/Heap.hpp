#pragma once

#include <utility>
#include <cinttypes>

template<typename T>
class Heap {
public:
    Heap(T arr[], std::size_t n)
    {
        for (intmax_t i = n / 2 - 1; i >= 0; --i) {
            heapify(arr, n, i);
        }
    }

    void heapify(T arr[], std::size_t n, std::size_t i)
    {
        std::size_t largest = i;
        std::size_t l = 2*i + 1;
        std::size_t r = 2*i + 2;

        if (l < n && arr[l] > arr[largest]) {
            largest = l;
        }

        if (r < n && arr[r] > arr[largest]) {
            largest = r;
        }

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

};

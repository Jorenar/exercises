#pragma once

#include "Heap.hpp"

namespace sorts {

template<class A>
void insertionSort(A& a)
{
    for (std::size_t i = 1; i < a.size; ++i) {
        typename A::type temp = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > temp) {
            a[j+1] = a[j];
            --j;
        }
        a[j+1] = temp;
    }
}

template<typename T>
void merge(T arr[], std::size_t p, std::size_t q, std::size_t r)
{
    std::size_t n1 = q - p + 1;
    std::size_t n2 = r - q;

    T* L = new T[n1];
    T* R = new T[n2];

    for (std::size_t i = 0; i < n1; i++) {
        L[i] = arr[p + i];
    }
    for (std::size_t j = 0; j < n2; j++) {
        R[j] = arr[q + 1 + j];
    }

    std::size_t i = 0;
    std::size_t j = 0;
    std::size_t k = p;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }

    delete[] L;
    delete[] R;
}

template<class A>
void mergeSort(A& a, std::size_t p, std::size_t r)
{
    if (p < r) {
        std::size_t q = (p+r)/2;
        mergeSort(a, p, q);
        mergeSort(a, q+1, r);
        merge(a.getData(), p, q, r);
    }
}

template<class A>
void heapSort(A& a, std::size_t n)
{
    auto arr = a.getData();
    Heap<typename A::type> h(arr, n);

    for (std::size_t i = n-1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        h.heapify(arr, i, 0);
    }
}

}

// vim: fdl=1

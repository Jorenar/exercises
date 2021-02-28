#pragma once

#include <cstdlib>
#include <initializer_list>
#include <iostream>

#include "sorts.hpp"

class ArrayException : public std::runtime_error {
public:
    ArrayException(const char*  msg) : runtime_error(msg) {}
    ArrayException(std::string& msg) : runtime_error(msg) {}
};

#include "util.hpp"

template<typename T, int N,
         typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
class Array {
    T data[N];

public:
    using type = T;
    const std::size_t size;

    Array() : size(N) {}

    Array(T min, T max) : size(N)
    {
        for (T& x: data) {
            x = rnd() % (max+1) + min;
        }
    }

    Array(std::initializer_list<T> l) : size(N)
    {
        if (l.size() != N) {
            throw ArrayException("Sizes of arrays don't match!");
        }

        int i = 0;
        for (auto x: l) {
            data[i++] = x;
        }
    }

    void print(int n = N)
    {
        int i;
        for (i = 0; i < n-1; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << data[i] << std::endl;
    }

    void sort(std::string t = "insertion")
    {
        if (t == "insertion") {
            sorts::insertionSort(*this);
        }
        else if (t == "merge") {
            sorts::mergeSort(*this, 0, N-1);
        }
        else if (t == "heap") {
            sorts::heapSort(*this, N);
        }
    }

    T operator [](int n) const { return data[n]; }
    T& operator [](int n) { return data[n]; }

    T& at(int n)
    {
        if (n > N) {
            throw ArrayException("Out of bounds!");
        }
        data[n];
    }

    friend std::ostream& operator <<(std::ostream& out, Array arr)
    {
        int i;
        for (i = 0; i < N-1; ++i) {
            out << arr[i] << " ";
        }
        return out << arr[i];
    }

    T* getData()
    {
        return data;
    }

};

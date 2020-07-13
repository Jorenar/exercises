#pragma once

#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "VectorTraits.hpp"

template <typename T, size_t N>
class Vector {
    T data[N];
  public:
    typedef T value_type;
    typedef std::size_t  size_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef typename VectorTraits<value_type>::ReturnType return_type;
    typedef typename VectorTraits<value_type>::ScalarType scalar_type;

    static const auto mult = VectorTraits<value_type>::mult;

    Vector() = default;
    Vector(const Vector& v) = default;
    Vector& operator =(const Vector& m) = default;

    Vector(const std::initializer_list<T>& list)
    {
        std::copy(list.begin(), list.end(), data);
    }

    size_type size() const
    {
        return N;
    }

    return_type get(size_type index) const
    {
        return data[index];
    }

    void set(size_type index, return_type value)
    {
        data[index] = value;
    }

    friend Vector operator *(scalar_type x, const Vector& v)
    {
        Vector result;
        for (int i=0; i < v.size(); ++i) {
            result.set(i, mult(x, v.get(i)));
        }
        return result;
    }

    friend std::ostream& operator <<(std::ostream& out, const Vector& v)
    {
        for (int i=0; i < v.size(); ++i) {
            out << v.get(i) << " ";
        }
        return out;
    }

    friend std::istream& operator >>(std::istream& in, Vector& v)
    {
        Vector::value_type value;
        for (int i=0; i < v.size(); ++i) {
            in >> value;
            if (in) {
                v.set(i, value);
            }
        }
        return in;
    }

};

// vim: fen fdl=1

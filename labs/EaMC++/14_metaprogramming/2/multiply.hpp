#pragma once

#include "dotProduct.hpp"

template<int N, int M, typename T>
constexpr void Multiply(T A[], T x[], T y[])
{
    if constexpr (N > 0) {
        y[N-1] = DotProduct<M>(A+((N-1)*M), x);
        Multiply<N-1,M>(A,x,y);
    }
}

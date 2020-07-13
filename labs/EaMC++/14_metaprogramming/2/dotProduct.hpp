#pragma once

template<int N, typename T>
constexpr T DotProduct(T a[], T b[])
{
    if constexpr (N > 0) {
        return a[N-1] * b[N-1] + DotProduct<N-1>(a,b);
    }
    else {
        return 0;
    }
}

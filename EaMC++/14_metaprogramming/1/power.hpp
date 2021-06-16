#pragma once

template<int n, int p>
struct Power {
    static constexpr int value = n * Power<n, p-1>::value;
};

template<int n>
struct Power<n,0> {
    static constexpr int value = 1;
};

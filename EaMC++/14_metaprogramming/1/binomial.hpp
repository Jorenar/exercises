#pragma once

template<int n, int k>
struct Binomial {
    static constexpr long long value = Binomial<n-1,k>::value + Binomial<n-1,k-1>::value;
};

template<int n>
struct Binomial<n,n> {
    static constexpr int value = 1;
};

template<int n>
struct Binomial<n,0> {
    static constexpr int value = 1;
};

// Jakub Lukasiewicz

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>

using ld  = long double;
using vec = std::vector<ld>;

/* Is this dynamic programming?
 *       _.._      _.._
 *     :'    \    /    `;
 *     (  `-. \()/_.-'  )
 *      \   (__()__)   /
 *       ),'  /()\  ',(
 *       \___/ () \___/
 */
uintmax_t factorial(const unsigned int n)
{
    static std::vector<uintmax_t> mem{ 1 };
    while (n >= mem.size()) {
        mem.emplace_back(mem.back() * mem.size());
    }
    return mem[n];
}

vec interpolate(const vec& X, const vec& Y)
{
    auto M = Y.size();

    vec W(M);

    vec f(M);
    vec foo(M);

    std::size_t l = 0;
    foo[0] = l;
    f[0] = Y[0];
    for (std::size_t i = 1; i < X.size(); ++i) {
        if (X[i-1] != X[i]) {
            l = i;
        }
        foo[i] = l;
        f[i] = Y[l];
    }

    for (std::size_t i = 0; i < X.size(); ++i) {
        for (std::size_t j = 0; j < f.size() - i; ++j) {
            if (X[j] == X[j + i]) {
                f[j] = Y[foo[j] + i] / factorial(i);
            }
            else {
                f[j] = (f[j+1] - f[j]) / (X[j+i] - X[j]);
            }
        }
        W[i] = f[0];
    }

    return W;
}

ld calc(const ld t, const vec& W, const vec& X)
{
    auto y = W.back();
    for (int i = W.size() - 2; i >= 0; --i) {
        y = y * (t - X[i]) + W[i];
    }
    return y;
}

int main()
{
    int M;
    int N;

    std::cin >> M >> N;

    vec X(M);
    vec Y(M);
    vec T(N);

    auto readVec = [](vec& V) {
                   for (auto& v: V) {
                       std::cin >> v;
                   }
               };
    readVec(X);
    readVec(Y);
    readVec(T);

    const vec W = interpolate(X, Y);

    std::cout << std::setprecision(16) << std::fixed;
    for (auto w: W) {
        std::cout << w << " ";
    }
    std::cout << "\n";

    for (auto& t: T) {
        std::cout << calc(t, W, X) << " ";
    }
    std::cout << std::endl;

    return 0;
}

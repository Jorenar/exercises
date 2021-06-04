// Jakub Lukasiewicz

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    std::size_t N; // size of matrix
    std::size_t M; // number of "ribbons"
    long double w; // omega
    std::size_t L; // number of iterations

    using V = std::vector<long double>;

    // read data {{{1

    std::cin >> N >> M;

    std::size_t foo = (M - 1) / 2;

    std::vector<V> ribbons(N);
    for (std::size_t i = 0; i < M; ++i) {
        auto s = N - foo + (i < (M+1)/2 ? i : M-i-1);
        ribbons[i].resize(s);
        for (auto& x: ribbons[i]) {
            std::cin >> x;
        }
    }

    V y(N);
    V x(N);

    auto readVec = [](V& vec) {
                       for (auto& e: vec) {
                           std::cin >> e;
                       }
                   };

    readVec(y);
    readVec(x);

    std::cin >> w >> L;

    // SOR {{{1

    auto getEl = [&ribbons, foo](std::size_t r, std::size_t c) {
                     return ribbons[r - c + foo][r < c ? r : c];
                 };

    for (std::size_t l = 0; l < L; ++l) {
        for (std::size_t i = 0; i < N; ++i) {
            auto temp = y[i];
            for (auto m = (foo < i ? i-foo : 0); m < std::min(i+foo+1, N); ++m) {
                if (m != i) {
                    temp -= getEl(i, m) * x[m];
                }
            }
            x[i] = (1-w) * x[i]  +  w * temp / getEl(i, i);
        }
    }

    // print {{{1

    std::cout << std::setprecision(16) << std::scientific;
    for (std::size_t i = 0; i < N; ++i) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;

    // }}}1

    return 0;
}

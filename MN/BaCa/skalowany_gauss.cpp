// Jakub Lukasiewicz

#include "vectalg.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

Vector solveEquations(const Matrix& A_org, const Vector& b_org, const double eps)
{
    using ld = long double;
    const auto n = A_org.size();

    Matrix A{ A_org };
    Vector b{ b_org };

    std::vector<ld> scales(n);
    for (std::size_t i = 0; i < n; ++i) {
        scales[i] = std::accumulate(A.begin() + i*n, A.begin() + (i+1)*n, 0.0,
                                    [](ld a, ld b) -> ld {
                                        return std::max(a, std::abs(b));
                                    });
    }

    std::vector<int> permutations(n);
    std::iota(permutations.begin(), permutations.end(), 0);

    for (std::size_t k = 0; k < n-1; ++k) {
        /* swap rows */ {
            auto row = k;
            ld   v   = 0;

            for (int r = k; r < n; ++r) {
                auto temp = std::abs(A(permutations[r], k) / scales[permutations[r]]);
                if (temp > v) {
                    row = r;
                    v = temp;
                }
            }

            if (row != k) {
                std::swap(permutations[k], permutations[row]);
            }
        }

        for (int r = k+1; r < n; ++r) {
            auto scale = A(permutations[r], k) / A(permutations[k], k);
            for (int v = k; v < n; ++v) {
                A(permutations[r], v) -= A(permutations[k], v) * scale;
            }
            b[permutations[r]] -= b[permutations[k]] * scale;
        }
    }

    Vector x(n);
    for (int i = n-1; i >= 0; --i) {
        ld temp = 0;
        for (int j = i+1; j < n; ++j) {
            temp += A(permutations[i], j) * x[j];
        }
        x[i] = (b[permutations[i]] - temp) / A(permutations[i], i);
    }

    auto r = residual_vector(A_org, b_org, x);
    if (r.max_norm() >= eps) {
        std::transform(x.begin(), x.end(),
                       solveEquations(A_org, r, eps).begin(),
                       x.begin(), std::plus<ld>());
    }

    return x;
}

// vim: fdl=1

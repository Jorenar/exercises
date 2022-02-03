// Jakub Lukasiewicz

#include <algorithm>

template<typename T>
inline int sgn(T x)
{
    return (T(0) < x) - (x < T(0));
}

double findZero(
    double (* f)(double), // function whose zero we are looking for in [a,b]
    double a,             // left end of the interval
    double b,             // right end of the interval
    int M,                // maximum allowed number of calls of the function f
    double eps,           // expected accuracy of zero
    double delta          // sufficient absolute error of the result
)
{
    using ld = long double;

    ld fa = f(a);
    ld fb = f(b);
    M -= 2;

    if (std::abs(fa) < eps) {
        return a;
    }

    if (std::abs(fb) < eps) {
        return b;
    }

    auto e  = b - a;

    auto c  = b;
    auto fc = fb;

    // Bisection method
    if (sgn(fa) != sgn(fb)) {
        while (M > 0) {
            e /= 2;
            c = a + e;

            fc = f(c);
            --M;

            if (std::abs(e) < delta || std::abs(fc) < eps) {
                return c;
            }
            else if (std::abs(e) < 0.1) {
                break;
            }

            if (sgn(fc) == sgn(fa)) {
                a  = c;
                fa = fc;
            }
        }
    }

    auto x0  = a;
    auto fx0 = fa;

    auto x1  = c;
    auto fx1 = fc;

    // Secant method
    while (M > 0) {
        ld x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        ld fx2 = f(x2);
        --M;

        if (std::abs(x2-x1) < delta || std::abs(fx2) < eps) {
            return x2;
        }

        x0  = x1;
        fx0 = fx1;

        x1  = x2;
        fx1 = fx2;
    }

    return x1;
}

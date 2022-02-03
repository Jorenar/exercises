// Jakub Lukasiewicz

#include <algorithm>

#include "source.h"

spline::spline(std::size_t n) : n(n) {}

void spline::set_points(const double x[], const double y[])
{
    arr h(new ld[n-1]);
    for (std::size_t i = 0; i < n-1; ++i) {
        h[i] = x[i+1] - x[i];
    }

    arr a(new ld[n-1]);
    for (std::size_t i = 1; i < n-1; ++i) {
        a[i] = 3 * ( (y[i+1]-y[i])/h[i] - (y[i] - y[i-1])/h[i-1] );
    }

    arr l(new ld[n]{ 1 });
    arr m(new ld[n]{ 0 });
    arr z(new ld[n]{ 0 });

    for (std::size_t i = 1; i < n-1; ++i) {
        l[i] = 2 * (x[i+1] - x[i-1]) - h[i-1] * m[i-1];
        m[i] = h[i] / l[i];
        z[i] = (a[i] - h[i-1]*z[i-1]) / l[i];
    }

    l[n-1] = 1;
    z[n-1] = 0;

    arr c(new ld[n]);
    arr b(new ld[n-1]);
    arr d(new ld[n-1]);

    c[n-1] = 0;

    for (std::size_t i = n-1; i--;) {
        c[i] = z[i] - m[i] * c[i+1];
        b[i] = (y[i+1] - y[i])/h[i] - h[i]*(c[i+1] + 2*c[i])/3;
        d[i] = (c[i+1] - c[i]) / (3*h[i]);
    }

    arr X(new ld[n]);
    std::copy(x, x+n, X.get());

    arr Y(new ld[n]);
    std::copy(y, y+n, Y.get());

    S = {
        std::move(Y),
        std::move(b),
        std::move(c),
        std::move(d),
        std::move(X)
    };
}

double spline::operator ()(const double x) const
{
    auto it = std::upper_bound(S.t.get(), S.t.get()+n, 0,
                               [x](const double& val, const double& e) {
                                   return x - e < val;
                               });
    std::size_t i = (it == S.t.get()+n ? 0 : std::distance(S.t.get(), it)-1);

    auto X = x - S.t[i];
    return S.a[i] + X*(S.b[i] + X*(S.c[i] + S.d[i]*X));
}

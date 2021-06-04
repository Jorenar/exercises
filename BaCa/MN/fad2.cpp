// Jakub Lukasiewicz

#include <cmath>
#include <iomanip>
#include <iostream>

#include "funkcja.h"

/* example "funkcja.h":
 *
 *     template <typename T>
 *     T funkcja(const T& x, const T& y){
 *         T w = sin(x*x - 2*(y+1))/exp(-y*y+cos(x*y));
 *         return w;
 *     }
 *
 */

enum class XY { X, Y };

class Jet {

    using ld = long double;

    ld v;
    ld dx;
    ld dy;
    ld dx2;
    ld dxy;
    ld dy2;

public:

    // Constructors {{{1

    Jet() : v(0), dx(0), dy(0), dx2(0), dxy(0), dy2(0) {}

    Jet(ld v_) : Jet()
    {
        v = v_;
    }

    Jet(ld v, XY t) : Jet(v)
    {
        dx = (t == XY::X);
        dy = (t == XY::Y);
    }

    Jet(ld v, ld dx, ld dy, ld dx2, ld dxy, ld dy2) :
        v(v), dx(dx), dy(dy), dx2(dx2), dxy(dxy), dy2(dy2)
    {}

    // Arithmetic operators {{{1

    friend Jet operator -(const Jet& f)
    {
        return {
            -f.v,
            -f.dx,
            -f.dy,
            -f.dx2,
            -f.dxy,
            -f.dy2
        };
    }

    friend Jet operator +(const Jet& f, const Jet& g)
    {
        return {
            f.v   + g.v,
            f.dx  + g.dx,
            f.dy  + g.dy,
            f.dx2 + g.dx2,
            f.dxy + g.dxy,
            f.dy2 + g.dy2
        };
    }

    friend Jet operator -(const Jet& f, const Jet& g)
    {
        return f + (-g);
    }

    friend Jet operator *(const Jet& f, const Jet& g)
    {
        return {
            f.v*g.v,
            f.dx*g.v + g.dx*f.v,
            f.dy*g.v + g.dy*f.v,
            2*f.dx*g.dx + f.dx2*g.v + g.dx2*f.v,
            f.dxy*g.v + g.dy*f.dx + g.dxy*f.v + f.dy*g.dx,
            2*f.dy*g.dy + f.dy2*g.v + g.dy2*f.v
        };
    }

    friend Jet operator /(const Jet& f, const Jet& g)
    {
        auto gv2 = std::pow(g.v, 2);
        auto gv3 = std::pow(g.v, 3);
        return {
            f.v/g.v,
            (f.dx*g.v - f.v*g.dx) / gv2,
            (f.dy*g.v - f.v*g.dy) / gv2,
            (-g.v*(2*f.dx*g.dx + f.v*g.dx2) + f.dx2*gv2 + 2*f.v*std::pow(g.dx,2)) / gv3,
            (-g.v*(f.dx*g.dy + f.dy*g.dx + f.v*g.dxy) + f.dxy*gv2 + 2*f.v*g.dx*g.dy) / gv3,
            (-g.v*(2*f.dy*g.dy + f.v*g.dy2) + f.dy2*gv2 + 2*f.v*std::pow(g.dy,2)) / gv3
        };
    }

    // Basic mathematical functions {{{1

    friend Jet sin(const Jet& f)
    {
        auto sfv = std::sin(f.v);
        auto cfv = std::cos(f.v);
        return {
            std::sin(f.v),
            std::cos(f.v)*f.dx,
            std::cos(f.v)*f.dy,
            cfv*f.dx2 - sfv*std::pow(f.dx,2),
            cfv*f.dxy - sfv*f.dx*f.dy,
            cfv*f.dy2 - sfv*std::pow(f.dy,2)
        };
    }

    friend Jet cos(const Jet& f)
    {
        auto sfv = std::sin(f.v);
        auto cfv = std::cos(f.v);
        return {
            cfv,
            -sfv*f.dx,
            -sfv*f.dy,
            -cfv*std::pow(f.dx,2) - sfv*f.dx2,
            -cfv*f.dx*f.dy        - sfv*f.dxy,
            -cfv*std::pow(f.dy,2) - sfv*f.dy2
        };
    }

    friend Jet exp(const Jet& f)
    {
        auto efv = std::exp(f.v);
        return {
            efv,
            efv * f.dx,
            efv * f.dy,
            efv * (std::pow(f.dx,2) + f.dx2),
            efv * (f.dx*f.dy + f.dxy),
            efv * (std::pow(f.dy,2) + f.dy2)
        };
    }

    // }}}1

    friend std::ostream& operator <<(std::ostream& output, const Jet& f)
    {
        return output
            << f.v   << " "
            << f.dx  << " "
            << f.dy  << " "
            << f.dx2 << " "
            << f.dxy << " "
            << f.dy2;
    }

};

int main()
{
    std::size_t M;
    std::cin >> M;

    std::cout << std::setprecision(16) << std::fixed;

    while (M--) {
        long double x;
        long double y;
        std::cin >> x >> y;
        std::cout << funkcja(Jet(x, XY::X), Jet(y, XY::Y)) << "\n";
    }

    return 0;
}

#include <cmath>
#include <fstream>
#include <iostream>
#include <cfloat>
#include <iomanip>
#include "cpp-bmp-images/BMP.h"

class PRNG {
    using base_type = uint32_t;
    base_type X[7]; // for convenience, 'p' is defined here as array size!
    std::size_t N;
    base_type a, b, c, m, p, q;
    double nextNormal;

public:

    PRNG(base_type seed = 2463534242) :
        N(sizeof(X)/sizeof(X[0])),
        a(13), b(17), c(5), m(1 << b), p(N), q(3),
        nextNormal(0)
    {
        seed += (seed % 1000) * b; // "twist"
        for (auto& x: X) { // Xorshift
            seed ^= (seed << a);
            seed  = (seed >> b);
            x = (seed ^= (seed << c));
        }
    }

    base_type operator ()()
    {
        auto P = (N-p) % p;
        auto Q = (N-q) % p;
        if (X[Q] % 2 == 0) {
            X[P] = (a*(X[P] + X[Q]) + c) % m;
        }
        else {
            X[P] = (a*(X[P] & X[Q]) + c) % m;
        }
        return X[P];
    }

    inline double uniform() { return static_cast<double>( (*this)() ) / m; }

    inline bool bernoulli(double P) { return uniform() <= P ? 1 : 0; }

    inline double exponential(double l) { return std::log(1 - uniform()) / -l; }

    std::size_t binomial(double P, std::size_t n)
    {
        auto val = 0;
        while (n--) {
            val += bernoulli(P);
        }
        return val;
    }

    base_type poisson(double l)
    {
        double L = std::exp(-l);
        base_type k = 0;
        double p = 1;
        do {
            ++k;
            p *= uniform();
        } while (p > L);
        return k-1;
    }

    double normal()
    {
        if (nextNormal != 0) {
            auto temp = nextNormal;
            nextNormal = 0;
            return temp;
        }
        auto r = std::sqrt(-2 * std::log(uniform()));
        auto s = 2 * M_PI * uniform();
        nextNormal = r * std::sin(s) + DBL_MIN;
        return r * std::cos(s);
    }

};

template<typename F>
void dat(std::string name, F func,
         const std::size_t s = 50, const std::size_t S = 0)
{
    const auto N = 100000;
    std::size_t temp[N]{ 0 };
    for (int i = 0; i < N; ++i) {
        ++temp[static_cast<std::size_t>(func())];
        switch (i+1) {
            case 100: case 1000: case 100000: {
                std::ofstream out{ "data/" + name + std::to_string(i+1) + ".dat" };
                out << "x y\n";
                auto n = S ? S : (s < i ? s : i);
                for (int j = 0; j < n; ++j) {
                    out << j << " " << temp[j] << "\n";
                }
                out.close();
            }
        }
    }
}

int main(int argc, char *argv[])
{

    if (argc > 1 && argv[1] == std::string("--print")) {
        PRNG gen{};
        for (int i = 10; i--; ) {
            std::cout << gen() << std::endl;
        }
        return 0;
    }

    /* distributions */ {
        PRNG gen{};

        dat("uniform",     [&]() { return int(10*gen.uniform()) % 10; }, 10);
        dat("bernoulli",   [&]() { return gen.bernoulli(0.6);         }, 2);
        dat("binomial",    [&]() { return gen.binomial(0.5, 10);      }, 10);
        dat("poisson",     [&]() { return gen.poisson(4);             }, 0, 25);
        dat("exponential", [&]() { return gen.exponential(1)*10;      });
        dat("normal",      [&]() { return gen.normal()*6 + 25;        });
    }

    /* BMP */ {
        PRNG gen{};

        const auto d = 64;
        BMP bmp(d, d);
        bmp.fill_region(0, 0, d, d, 255, 255, 255, 255);
        for (int i = 0; i < d; ++i) {
            for (int j = 0; j < d; ++j) {
                if (gen() % 2) {
                    bmp.fill_region(i, j, 1, 1, 0, 0, 0, 255);
                }
            }
        }
        bmp.write("data/test.bmp");
    }

    if (argc > 1 && argv[1] == std::string("--testing")) {
        PRNG gen{};
        std::ofstream out{ "data/testing.dat" };
        const auto n = 1e9;
        const auto b = 17;
        const auto s = std::to_string(1 << b).length();
        out << "#==================================================================\n"
            << "# generator my_prng  seed = 2463534242\n"
            << "#==================================================================\n";
        out << "type: d\n"
            << "count: " << n << "\n"
            << "numbit: " << b << "\n";
        for (std::size_t i = 0; i < n; ++i) {
            out << std::right << std::setw(s) << gen() << "\n";
        }
        out.close();
    }

    return 0;
}

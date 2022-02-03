// Jakub Lukasiewicz

#ifndef SOURCE_H_
#define SOURCE_H_

#include <memory>

class spline {
    using ld = double;
    using arr = std::unique_ptr<ld[]>;
    const std::size_t n;
    struct {
        arr a, b, c, d;
        arr t;
    } S;
public:
    spline(std::size_t n);
    void set_points(const double x[], const double y[]);
    double operator ()(const double z) const;
};

#endif // SOURCE_H_

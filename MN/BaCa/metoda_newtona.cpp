// Jakub Łukasiewicz

#include <cmath>
#include <iterator>
#include <iomanip>
#include <iostream>

const double EPS = 1e-14;

const std::size_t MAX_ITER = 100;

void printVector(const double* x, unsigned int N)
{
    std::cout << std::setprecision(17) << std::fixed;
    for (unsigned int i = 0; i < N; ++i) {
        std::cout << x[i] << " ";
    }
    std::cout << "\n";
}

typedef void (*FuncPointer)(const double* x, double* y, double* Df);

int findCurve(FuncPointer f, double* x,
              unsigned int k,
              double h)
{
    double X[3] = { x[0], x[1], x[2] };
    double Y[2];
    double Df[2*3];

    for (std::size_t i = 0; i < k; ++i) {
        X[2] += h;

        for (std::size_t m = 0; m < ::MAX_ITER; ++m) {
            f(X, Y, Df);

            if (std::max(std::abs(Y[0]), std::abs(Y[1])) <= ::EPS) {
                break;
            }

            double W = Df[0] * Df[4] - Df[1] * Df[3];

            if (std::abs(W) < ::EPS || m == ::MAX_ITER-1) {
                return i+1;
            }

            X[0] -= (Y[0] * Df[4] - Y[1] * Df[1]) / W;
            X[1] -= (Y[1] * Df[0] - Y[0] * Df[3]) / W;
        }

        printVector(X, 3);
    }

    return 0;
}

int findSurface(FuncPointer f, double* x,
                unsigned int k1, unsigned int k2,
                double h1, double h2)
{
    double X[3] = { x[0], x[1], x[2] };
    double Y[1];
    double Df[1*3];

    const double X2 = X[2];

    for (std::size_t i = 0; i < k1; ++i) {
        X[1] += h1;
        X[2] = X2;
        for (std::size_t j = 0; j < k2; ++j) {
            X[2] += h2;

            for (std::size_t m = 0; m < ::MAX_ITER; ++m) {
                f(X, Y, Df);

                if (std::abs(Y[0]) <= ::EPS) {
                    break;
                }

                double W = Df[0];

                if (std::abs(W) < ::EPS || m == ::MAX_ITER-1) {
                    return (i+1)*k1 + (j+1);
                }

                X[0] -= Y[0] / W;
            }

            printVector(X, 3);
        }
        std::cout << "\n";
    }

    return 0;
}

int findFixedPoints(FuncPointer f, double* x,
                    unsigned int k1, unsigned int k2,
                    double h1, double h2)
{
    double X[4] = { x[0], x[1], x[2], x[3] };
    double Y[2];
    double Df[2*4];

    const double X3 = X[3];

    for (std::size_t i = 0; i < k1; ++i) {
        X[2] += h1;
        X[3] = X3;
        for (std::size_t j = 0; j < k2; ++j) {
            X[3] += h2;

            for (std::size_t m = 0; m < ::MAX_ITER; ++m) {
                f(X, Y, Df);

                double y[2] = { Y[0] - X[0], Y[1] - X[1] };

                if (std::max(std::abs(y[0]), std::abs(y[1])) <= ::EPS) {
                    break;
                }

                Df[0]--;
                Df[5]--;
                double W = Df[0] * Df[5] - Df[1] * Df[4];

                if (std::abs(W) < ::EPS || m == ::MAX_ITER-1) {
                    return (i+1)*k1 + (j+1);
                }

                X[0] -= (y[0] * Df[5] - y[1] * Df[1]) / W;
                X[1] -= (y[1] * Df[0] - y[0] * Df[4]) / W;
            }

            printVector(X, 4);
        }
        std::cout << "\n";
    }

    return 0;
}

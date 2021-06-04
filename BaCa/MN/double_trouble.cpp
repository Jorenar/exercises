// Jakub Łukasiewicz

// Forbidden: lοng

// Solution:
// Change recursive form
//             x_{k+1} = \frac{50}{7} x_k - x_{k+1}
// into closed-form expression using characteristic equation
//             t^2 - \frac{50}{7} t + 1 = 0
// which roots are:  t_1 = 1/7   t_2 = 7
// Then solve equation system from:
//             x_2 = \frac{50}{7} x_1 - x_0 = A * 7^{-2} + B * 7^2
//             x_3 = ...
// to get A and B

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    std::size_t z;
    std::cin >> z;

    while (z--) {
        double x0;
        double x1;
        unsigned short n;
        std::cin >> x0 >> x1 >> n;

        std::vector<int> K;
        while (n--) {
            unsigned int k;
            std::cin >> k;
            K.emplace_back(k);
        }

        double A = 7*(7*x0 - x1) / 48;
        double B = (7*x1 - x0) / 48;

        double xk;
        for (auto& k: K) {
            switch (k) {
                case 0:
                    xk = x0;
                    break;
                case 1:
                    xk = x1;
                    break;
                default:
                    xk = A * std::pow(7, -k) + B * std::pow(7, k);
            }
            std::cout << std::setprecision(15) << std::scientific << xk << "\n";
        }
        std::cout << std::endl;
    }

    return 0;
}

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

#include "LinkedQueue.hpp"

void radix(std::vector<int>& v)
{
    if (v.empty()) {
        return;
    }

    std::array<Queue<int>, 10> queues;

#if 0 // superfluous check
    auto m = *std::max_element(v.begin(), v.end());
    auto check = [&](auto ex) { return (m/ex > 0); };
#else
    auto check = [](auto) { return true; };
#endif

    for (unsigned int exp = 1; check(exp); exp *= 10) {
        for (const auto& x: v) {
            queues[(x/exp) % 10].push(x);
        }

        if (queues[0].size() == v.size()) {
            return;
        }

        v.clear();

        for (auto& q: queues) {
            while (!q.empty()) {
                v.push_back(q.pop());
            }
        }
    }
}

int main ()
{
    int x;
    std::vector<int> v;

    while (std::cin >> x) {
        v.push_back(x);
    }

    radix(v);

    for (const auto& i: v) {
        std::cout << i << '\n';
    }

    return 0;
}

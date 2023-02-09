#include <iostream>
#include <random>

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::mt19937 mt(std::random_device{}());
    using ud = std::uniform_int_distribution<int>;

    ud genOpt(0, 2);
    ud genVal(0, 1e6);
    ud genSize(1, 1006); // 1006 <= 1e6   (1e6 == 10^6)

    std::size_t n = genSize(mt);
    const char operations[] = { 'A', 'D', 'S' };

    std::cout << n << '\n';

    while (n--) {
        const char opt = operations[genOpt(mt)];
        std::cout << opt;
        if (opt == 'A') {
            std::cout << " " << genVal(mt);
        }
        std::cout << '\n';
    }

    return 0;
}

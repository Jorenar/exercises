#include <iostream>
#include <random>

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);

    std::mt19937 mt(std::random_device{}());
    using ud = std::uniform_int_distribution<unsigned int>;

    ud genOpt(0, 5);
    ud genVal(0, 1e3);
    ud genSize(1, 1e3);

    std::size_t n = argc > 1 ? std::stoull(argv[1]) : genSize(mt);
    const char operations[] = { 'F', 'B', 'f', 'b', 'R', 'S' };

    std::cout << n << '\n';

    while (n--) {
        const char opt = operations[genOpt(mt)];
        std::cout << opt;
        if (opt == 'F' || opt == 'B') {
            std::cout << " " << genVal(mt);
        }
        if (opt == 'R') {
            std::cout << " " << genVal(mt) << " " << genVal(mt);
        }
        std::cout << '\n';
    }

    return 0;
}

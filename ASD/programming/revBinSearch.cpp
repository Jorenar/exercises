#include <iostream>
#include <vector>

int revBinSearch(int x, int N)
{
    int p = 0;
    int q = N-1;
    int L = 0;

    while (p <= q) {
        ++L;

        int i = (p + q) / 2;

        if (i == x) {
            return L;
        }

        if (x < i) {
            q = i - 1;
        }
        else {
            p = i + 1;
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{
    const int MAXN = 10000;

    int i;
    int L;

    if (argc == 3) {
        i = std::stoi(argv[1]);
        L = std::stoi(argv[2]);
    }
    else {
        std::cin >> i >> L;
    }

    std::vector<std::pair<int, int> > results{};

    for (int n = i; n < MAXN; ++n) {
        if (revBinSearch(i, n) == L) {
            if (!results.empty() && results.back().second == n-1) {
                results.back().second = n;
            }
            else {
                results.push_back({ n, n });
            }
        }
    }

    std::cout << results.size() << "\n";
    for (auto& r: results) {
        std::cout << r.first << " " << r.second << "\n";
    }

    return 0;
}

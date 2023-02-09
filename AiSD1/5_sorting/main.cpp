// That's just so wrong...
#ifndef MAIN_CPP_
#define MAIN_CPP_

#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

template<typename T>
int sort(std::vector<T>&);

const char* filename();

int main(int argc, char*[])
{
    std::vector<int> nums;

    int in;
    while (std::cin >> in) {
        nums.push_back(in);
    }

    namespace sc = std::chrono;

    auto start = sc::steady_clock::now();
    auto ret = sort(nums);
    auto end = sc::steady_clock::now();

    if (argc == 1) {
        for (const auto& i: nums) {
            std::cout << i << '\n';
        }
    }
    else {
        auto elapsed = sc::duration_cast<sc::nanoseconds>(end - start);
        std::cout << nums.size() << " " << elapsed.count() << '\n';

        if (ret != 0) {
            std::ofstream out { "data/InsertionSort_oper.txt", std::ios::app };
            out << nums.size() << " " << ret << '\n';
            out.close();
        }
    }

    return 0;
}

#endif // MAIN_CPP_

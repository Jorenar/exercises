#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

template<int N>
struct Array {
    int a[N];
    int value = 1;
    long long sum = 0;

    std::mutex mutex1;
    std::mutex mutex2;
    std::mutex mutex3;

    int f(int x)
    {
        int y = x%11;
        return (y*y+1);
    }

    void generateArray()
    {
        static int i = 0;
        while (i < N) {
            std::lock_guard<std::mutex> lockGuard(mutex1);
            if (i < N) {
                a[i++] = rand();
            }
        }
        static int j = 0;
        while (j < N) {
            std::lock_guard<std::mutex> lockGuard(mutex2);
            if (j < N) {
                a[j] = f(a[j]);
                ++j;
            }
        }
    }

    long long computeSum()
    {
        static int i = 0;
        while (i < N) {
            std::lock_guard<std::mutex> lockGuard(mutex3);
                sum += i < N ? a[i++] : 0;
        }
        return sum;
    }

};

int main(int argc, char *argv[])
{
    int T = argc > 1 ? std::stoi(argv[1]) : 2;

    srand(2019);
    using A = Array<1000>;
    A array;

    std::vector<std::thread> threads;

    auto join = [&](auto t) {
                    while (t) {
                        threads.at(t-1).join();
                        threads.pop_back();
                        t = threads.size();
                    }
                };

    for (int i = 0; i < T; ++i) {
        threads.push_back(std::thread(&A::generateArray, &array));
    }
    join(threads.size());

    for (int i = 0; i < T; ++i) {
        threads.push_back(std::thread(&A::computeSum, &array));
    }
    join(threads.size());

    std::cout << "sum = " << array.sum << std::endl;
}

// vim: fen fdl=1

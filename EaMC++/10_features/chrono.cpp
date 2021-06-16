#include <chrono>
#include <iostream>
#include <string>

using namespace std::chrono;

class Timer {
    std::string name;
    time_point<steady_clock> start;

  public:

    Timer(const std::string& name) : name(name), start(steady_clock::now()) {}

    ~Timer()
    {
        duration<double, std::milli> diff = steady_clock::now() - start;
        std::cout << name << " : " << diff.count() << " ms" << std::endl;
    }

    auto durationInNanoseconds()
    {
        auto now = steady_clock::now();
        return duration_cast<nanoseconds>(now - start).count();
    }

};

long fibonacci(unsigned n)
{
    if (n < 2) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    Timer total("Total time");
    for (auto n: { 1, 5, 15, 20, 25, 40, 45 }) {
        Timer t("fibonacci(" + std::to_string(n) + ")");
        fibonacci(n);
    }
    std::cout << "Elapsed " << total.durationInNanoseconds() << " ns" << std::endl;
}

/** Expected output similar to:

   fibonacci(1) : 0.000619 ms.
   fibonacci(5) : 0.000891 ms.
   fibonacci(15) : 0.01025 ms.
   fibonacci(20) : 0.094905 ms.
   fibonacci(25) : 1.04443 ms.
   fibonacci(40) : 989.97 ms.
   fibonacci(45) : 8537.47 ms.
   Elapsed 9528821533 ns.
   Total time : 9528.84 ms.
 */

#include <algorithm>
#include <fstream>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

using uLL = unsigned long long;

uLL count(const std::string& path, std::promise<uLL> prom)
{
    std::ifstream file(path);
    if (file.fail()) {
        std::cerr << "Error while opening file '" << path << "'" << std::endl;
        exit(1);
    }

    uLL sum = 0;

    char x;
    while (file >> x) {
        sum += x;
    }
    file.close();

    prom.set_value(sum);

    return sum;
}

template<typename T>
class Counter {
    uLL s;
    std::promise<T> prom;
    std::future<T> fut;
    std::thread th;

    bool gotFuture;
  public:
    std::string path;

    Counter(std::string path) :
        s(0), fut(prom.get_future()),
        th(std::thread(count, path, std::move(prom))),
        path(path)
    {}

    uLL sum()
    {
        if (!gotFuture) {
            s = fut.get();
            gotFuture = true;
        }
        return s;
    }

    void join()
    {
        th.join();
    }

};

int main(int argc, char* argv[])
{
    using C = Counter<uLL>;
    std::vector<C> counters;

    for (int i = 1; i < argc; ++i) {
        counters.push_back(C(argv[i]));
    }

    for (auto& c: counters) {
        c.join();
    }

    std::sort(counters.begin(), counters.end(),
              [](auto& a, auto& c) { return a.sum() < c.sum(); });

    for (size_t i = 0; i < counters.size(); ++i) {
        for (size_t j = i; j < counters.size(); ++j) {
            if (counters.at(i).sum() == counters.at(j).sum()) {
                std::cout << counters.at(i).path << " == "
                    << counters.at(j).path << std::endl;
            }
            else {
                break;
            }
        }
    }

    return 0;
}

// vim: fen

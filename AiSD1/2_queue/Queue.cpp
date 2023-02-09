#include <iostream>
#include <stdexcept>

#include "ArrayQueue.hpp"

int main()
{
    int n; // number of instructions
    int x; // value to push on queue
    char operation; // operation to execute

#if defined(ARRAYQUEUE_HPP_)
    Queue<int> queue{ static_cast<std::size_t>(1e6) };
#elif defined(LINKEDQUEUE_HPP_)
    Queue<int> queue;
#else
#  error No queue!
#endif

    std::cin >> n;

    while (n--) {
        std::cin >> operation;
        try {
            switch (operation) {
                case 'A':
                    std::cin >> x;
                    queue.push(x);
                    break;

                case 'D':
                    if (queue.empty()) {
                        std::cout << "EMPTY" << '\n';
                        break;
                    }
                    std::cout << queue.pop() << '\n';
                    break;

                case 'S':
                    std::cout << queue.size() << '\n';
                    break;

                default:
                    throw std::runtime_error("unknown operation");
            }
        }
        catch (std::runtime_error& e) {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}

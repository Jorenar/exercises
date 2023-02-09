#include <iostream>
#include <stdexcept>

#include "ArrayStack.hpp"

int main()
{
    int n; // number of instructions
    int x; // value to push on stack
    char operation; // operation to execute
    Stack stack{ static_cast<std::size_t>(1e6) };

    std::cin >> n;

    while (n--) {
        std::cin >> operation;
        try {
            switch (operation) {
                case 'A':
                    std::cin >> x;
                    stack.push(x);
                    break;

                case 'D':
                    if (stack.empty()) {
                        std::cout << "EMPTY" << '\n';
                        break;
                    }
                    std::cout << stack.pop() << '\n';
                    break;

                case 'S':
                    std::cout << stack.size() << '\n';
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

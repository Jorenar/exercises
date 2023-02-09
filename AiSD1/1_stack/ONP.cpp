#include <iostream>
#include <string>

#include "LinkedStack.hpp"
// ^ Template implementation would make more sense,
// but this one doesn't require assumtions about size.

int main()
{
    Stack stack;
    std::string in;
    std::string space = "";

    while (std::cin >> in) {
        char c = in[0];
        if (c >= '0' && c <= '9') { // digit
            std::cout << space << in;
            space = " ";
        }
        else if (c == ')') { // print operator
            std::cout << " " << static_cast<char>(stack.pop());
            // a downside of using stack defined for `int`: casting to `char`
        }
        else if (c != '(') { // push operator on stack
            stack.push(c);
        }
    }
    std::cout << '\n';

    return 0;
}

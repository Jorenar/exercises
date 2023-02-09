#include <iostream>

#ifdef ARRAY
#  include "ArrayList.hpp"
#else
#  include "CursorList.hpp"
#endif

int main()
{
    int n; // number of instructions
    int x; // value to push on list (or replace in case of 'R' operation)
    int y; // value to replace x with in case of 'R' operation
    char operation; // operation to execute

    List<int, 1000> list;

    std::cin >> n;

    while (n--) {
        std::cin >> operation;

#if DEBUG == 2
            std::cerr << "Operation: " << operation << '\n'
                      << "Instructions left: " << n << std::endl;
#endif

        try {
            switch (operation) {
#if DEBUG
                case 'r':
                    std::cin >> x;
                    std::cerr << "Removed " << list.remove(x) << " item(s)\n";
                    break;

                case 'p':
                    list.print();
                    break;

                case 'q':
                    goto finish;
                    break;
                    // case 'q'
#endif

                case 'F':
                    std::cin >> x;
                    list.push_front(x);
                    break;

                case 'B':
                    std::cin >> x;
                    list.push_back(x);
                    break;

                case 'f':
                case 'b':
                    if (list.empty()) {
                        std::cout << "EMPTY" << '\n';
                        break;
                    }

                    if (operation == 'f') {
                        std::cout << list.pop_front() << '\n';
                    }
                    else {
                        std::cout << list.pop_back() << '\n';
                    }

                    break;

                case 'R':
                    std::cin >> x >> y;
                    if (list.replace(x, y)) {
                        std::cout << "TRUE" << '\n';
                    }
                    else {
                        std::cout << "FALSE" << '\n';
                    }

                    /* There are two reasons for adding additional method
                     * to interface:
                     *  1. not looping through the list twice
                     *  2. internal "direction" of data is in reverse
                     *     compared to this operation;
                     *     adding this method limited the need of rewriting
                     * Otherwise it would be:
                     *     if ((pos = list.find(x)) >= 0) {
                     *         auto p = static_cast<std::size_t>(pos);
                     *         list.insert(p, y);
                     *         list.erase(p+1);
                     *         std::cout << "TRUE" << '\n';
                     *     }
                     *     else {
                     *         std::cout << "FALSE" << '\n';
                     *     }
                     */
                    break;

                case 'S':
                    std::cout << list.size() << '\n';
                    break;

                default:
                    throw std::runtime_error("unknown operation");
            }
#if DEBUG == 2
            list.print();
#endif
        }
        catch (std::runtime_error& e) {
            std::cerr << e.what() << '\n';
            if (std::string(e.what()) == "unknown operation") {
                ++n;
            }
        }
    }

#if DEBUG == 1
    list.print();
#endif

#ifdef DEBUG
finish:
#endif

    return 0;
}

// vim: fdl=4

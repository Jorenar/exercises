#include <iostream>

#include "BinaryTree.hpp"

int main()
{
    BinaryTree<int> tree;

    int n;
    std::cin >> n;

    for (int in; n; --n) {
        std::cin >> in;
        tree.insert(in);
    }

    std::cout << tree.size() << " "
              << tree.depth() << " "
              << tree.minimum() << " "
              << tree.maximum() << '\n';
    tree.preorder();
    for (auto i = 1; i < 10; ++i) {
        std::cout << (tree.search(i) ? "Yes" : "No") << '\n';
    }

    return 0;
}

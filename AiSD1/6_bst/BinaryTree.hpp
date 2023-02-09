#ifndef BINARYTREE_HPP_
#define BINARYTREE_HPP_

#include <memory>
#include <iostream>

template<typename T>
class BinaryTree {
    struct Node {
        T value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        Node* parent;

        Node() : value(0), left(nullptr), right(nullptr), parent(nullptr) {}
        Node(T x) : value(x), left(nullptr), right(nullptr), parent(nullptr) {}

        inline void print() { std::cout << value << " "; }
    };

    using shrNode = std::shared_ptr<Node>;

    shrNode root;
    std::size_t count;

    shrNode erase(shrNode t, T x);
    std::size_t depth(shrNode t);

    void preorder(shrNode t);
    void inorder(shrNode t);
    void postorder(shrNode t);

    shrNode searchRecursive(T x, shrNode t);
    shrNode findExtremum(shrNode t, bool searchMin);

public:
    BinaryTree();

    shrNode insert(int x);
    void erase(T x);

    std::size_t size();
    std::size_t depth();

    T minimum();
    T maximum();

    shrNode search(T x);
    shrNode searchRecursive(T x);

    void preorder();
    void inorder();
    void postorder();
};

#include "BinaryTree.ipp"

#endif // BINARYTREE_HPP_

// vim: fdl=1

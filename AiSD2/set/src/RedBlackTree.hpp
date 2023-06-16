#ifndef REDBLACKTREE_HPP_
#define REDBLACKTREE_HPP_

#include "BinaryTree.hpp"

namespace rbtree {

enum class Color { Red, Black };

template<typename T>
struct Node {
    T value;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node() {}

    Node(Node* guard) :
        value(0), color{Color::Black}, left(guard), right(guard), parent(guard)
    {}

    Node(Node* guard, T x) :
        value(x), color{Color::Black}, left(guard), right(guard), parent(guard)
    {}

    inline void print() const
    {
        char c = (color == Color::Red) ? 'R' : 'B';
        std::cout << value << "(" << c << ")" << " ";
    }
};

} // namespace rbtree

template<typename T>
class RedBlackTree : public BinaryTree<T, rbtree::Node<T> > {
protected:
    using Node = rbtree::Node<T>;
    using Base = BinaryTree<T, Node>;

    void fixupInsert(Node*);
    void fixupRemove(Node*);

    void rotateLeft(Node*);
    void rotateRight(Node*);

public:
    Node* insert(T);

    //  CLRS makes some changes to the method, so instead of changing
    //    BinaryTree just reimplement it for RedBlackTree
    void remove(T);

    inline void erase(T); // alias remove()
};

#include "RedBlackTree.ipp"

#endif // REDBLACKTREE_HPP_

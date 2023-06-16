#ifndef BINARYTREE_HPP_
#define BINARYTREE_HPP_

#include <iostream>

namespace bintree {

template<typename T>
struct Node {
    T value;
    Node* left;
    Node* right;
    Node* parent;

    Node() : value(0), left(nullptr), right(nullptr), parent(nullptr) {}
    Node(T x) : value(x), left(nullptr), right(nullptr), parent(nullptr) {}

    Node(Node* guard) : value(0), left(guard), right(guard), parent(guard) {}
    Node(Node* guard, T x) : value(x), left(guard), right(guard), parent(guard) {}

    inline void print() const { std::cout << value << " "; }
};

} // namespace bintree

template<typename T, class Node = bintree::Node<T> >
class BinaryTree {
protected:
    Node* const guard;

    Node* root;
    std::size_t count;

    Node* findExtremum(Node* t, bool searchMin) const;
private:
    Node* erase(Node* t, T x);

    std::size_t depth(Node* t) const;

    void preorder(Node* t) const;
    void inorder(Node* t) const;
    void postorder(Node* t) const;

    Node* searchRecursive(T x, Node* t) const;

    void deleteAllChildNodes(Node*);
public:
    BinaryTree();
    ~BinaryTree();

    Node* insert(int x);
    void erase(T x);

    bool isEmpty() const;
    std::size_t size() const;
    std::size_t depth() const;

    T minimum() const;
    T maximum() const;

    Node* search(T x) const;
    Node* searchRecursive(T x) const;

    void preorder() const;
    void inorder() const;
    void postorder() const;
};

#include "BinaryTree.ipp"

#endif // BINARYTREE_HPP_

// vim: fdl=1

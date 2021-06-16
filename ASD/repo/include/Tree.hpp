#pragma once

#include <memory>
#include <iostream>

template<typename T>
class Tree {
protected:
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

    void preorder(shrNode t)
    {
        if (t != nullptr) {
            t->print(); // is printed before calling recursively for children
            preorder(t->left);
            preorder(t->right);
        }
    }

    void inorder(shrNode t)
    {
        if (t != nullptr) {
            inorder(t->left);
            t->print(); // is printed in between recursive call with children
            inorder(t->right);
        }
    }

    void postorder(shrNode t)
    {
        if (t != nullptr) {
            postorder(t->left);
            postorder(t->right);
            t->print(); // printing after recursion
        }
    }

public:
    Tree() : root(nullptr) {}

    void print(std::string order)
    {
        if (order == "pre") {
            preorder(root);
        }
        else if (order == "in") {
            inorder(root);
        }
        else if (order == "post") {
            postorder(root);
        }
        else {
            std::cout << "Unknown order";
        }
        std::cout << std::endl;
    }

};

// vim: fdl=2

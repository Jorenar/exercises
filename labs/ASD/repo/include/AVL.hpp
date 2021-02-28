#pragma once

#include <memory>

#include "Tree.hpp"

template<typename T>
class AVL : public Tree<T> {
    using typename Tree<T>::Node;
    using typename Tree<T>::shrNode;

    shrNode& root;

public:
    AVL() : Tree<T>(), root(Tree<T>::root) {}

    int height(shrNode t)
    {
        int h = 0;
        if (t != nullptr) {
            int l_height = height(t->left);
            int r_height = height(t->right);
            int max_height = std::max(l_height, r_height);
            h = max_height + 1;
        }
        return h;
    }

    int difference(shrNode t)
    {
        int l_height = height(t->left);
        int r_height = height(t->right);
        int b_factor = l_height - r_height;
        return b_factor;
    }

    shrNode rr_rotate(shrNode parent)
    {
        shrNode t;
        t = parent->right;
        parent->right = t->left;
        t->left = parent;
        return t;
    }

    shrNode ll_rotate(shrNode parent)
    {
        shrNode t;
        t = parent->left;
        parent->left = t->right;
        t->right = parent;
        return t;
    }

    shrNode lr_rotate(shrNode parent)
    {
        shrNode t;
        t = parent->left;
        parent->left = rr_rotate(t);
        return ll_rotate(parent);
    }

    shrNode rl_rotate(shrNode parent)
    {
        shrNode t;
        t = parent->right;
        parent->right = ll_rotate(t);
        return rr_rotate(parent);
    }

    shrNode balance(shrNode t)
    {
        int bal_factor = difference(t);
        if (bal_factor > 1) {
            if (difference(t->left) > 0) {
                t = ll_rotate(t);
            }
            else {
                t = lr_rotate(t);
            }
        }
        else if (bal_factor < -1) {
            if (difference(t->right) > 0) {
                t = rl_rotate(t);
            }
            else {
                t = rr_rotate(t);
            }
        }
        return t;
    }

    shrNode insert(shrNode& t, T x)
    {
        if (t == nullptr) {
            t = std::make_shared<Node>(x);
        }
        else if (x < t->value) {
            t->left = insert(t->left, x);
            t = balance(t);
        }
        else if (x >= t->value) {
            t->right = insert(t->right, x);
            t = balance(t);
        }
        return t;
    }

    shrNode insert(T x)
    {
        return insert(root, x);
    }

};

// vim: fdl=2

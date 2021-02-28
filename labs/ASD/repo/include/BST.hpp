#pragma once

#include <memory>

#include "Tree.hpp"

template<typename T>
class BST : public Tree<T> {
    using typename Tree<T>::Node;
    using typename Tree<T>::shrNode;
    shrNode& root;

public:
    BST() : Tree<T>(), root(Tree<T>::root) {}

    shrNode findExtremum(shrNode t, bool searchMin) { // searching in branch
        shrNode p  = nullptr;
        while (t != nullptr) {
            p = t;
            t = searchMin ? t->left : t->right;
        }
        return p;
    }

    shrNode remove(shrNode t, int x) {
        if (t != nullptr) { // traverse tree until `null`
            if (x < t->value) {
                t->left = remove(t->left, x);
            } else if (x > t->value) {
                t->right = remove(t->right, x);
            } else { // if `x` is same as `t->value`, then this is the node to be deleted

                // Node with only one child or no child
                if (t->left == nullptr) {
                    return t->right;
                } else if (t->right == nullptr) {
                    return t->left;
                }

                t->value = findExtremum(t->right, true)->value; // node with two children; get smallest to the right branch
                //                                ^^^^ = search for mininmum

                t->right = remove(t->right, t->value); // remove the inorder successor
            }
        }

        return t;
    }

    shrNode min() {
        return findExtremum(root, true);
    }

    shrNode max() {
        return findExtremum(root, false);
    }

    shrNode search(int x) {
        shrNode t = root;
        while (t != nullptr && t->value != x) {
            t = x < t->value ? t->left : t->right;
        }
        return t;
    }

    shrNode insert(int x) {
        shrNode s = std::make_shared<Node>(x);

        if (root == nullptr) { // insert as first element
            root = std::move(s);
        } else { // inser after traversing tree
            Node* t = root.get();
            Node* p = nullptr;
            while (t != nullptr) { // find right place; one loop - linear complexity
                p = t;
                t = x < t->value ? t->left.get() : t->right.get();
            }
            s->parent = p;
            if (x < p->value) {
                p->left = std::move(s);
            } else {
                p->right = std::move(s);
            }
        }

        return s;
    }

    void remove(int x) {
        root = remove(root, x);
    }

};

// vim: fdl=2

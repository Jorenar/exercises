#pragma once

#include <stack>

template<std::size_t N>
class Ex_1_29 {

    struct Node {
        std::size_t val;
        Node* prev;
        Node* next;

        Node(std::size_t i, Node* n) : val{i}, prev{}, next{n} {}
    };

    Node* root;

    std::stack<Node*> helper[N];

public:

    Ex_1_29() : root{} {}

    void push(std::size_t i)
    {
        Node* temp = new Node(i, root);
        if (root != nullptr) {
            root->prev = temp;
        }
        root = temp;
        helper[i].push(temp);
    }

    std::size_t pop()
    {
        if (root == nullptr) {
            return 0;
        }

        std::size_t i = root->val;
        helper[i].pop();
        if (root->next) {
            root->next->prev = nullptr;
        }
        root = root->next;
        return i;
    }

    bool search(std::size_t i)
    {
        return !helper[i].empty();
    }

    void remove(std::size_t i)
    {
        if (helper[i].top() == root) {
            pop();
        }
        else {
            Node* temp = helper[i].pop();
            if (temp->prev) {
                temp->prev->next = temp->next;
            }
            if (temp->next) {
                temp->next->prev = temp->prev;
            }
            delete temp;
        }
    }

};

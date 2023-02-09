#ifndef LINKEDSTACK_HPP_
#define LINKEDSTACK_HPP_

#ifdef STACK_IMPLEMENTED
#  error Stack class already implemented
#endif

#include <cstddef>
#include <memory>

class Stack {
    std::size_t capacity;
    std::size_t count;

    struct Node;
    using nodePtr = std::unique_ptr<Node>;
    struct Node {
        int value;
        nodePtr prev;
        Node(int, nodePtr);
    };
    nodePtr head;
public:
    Stack(std::size_t = 0); // capacity set to 0 means infinity

    void push(int x);
    int pop();

    bool empty() const;
    std::size_t size() const;
};

#define STACK_IMPLEMENTED

#endif // LINKEDSTACK_HPP_

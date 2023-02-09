#ifndef LINKEDQUEUE_HPP_
#define LINKEDQUEUE_HPP_

#include <cstddef>
#include <memory>

template<typename T>
class Queue {
    std::size_t count;

    struct Node;
    using nodePtr = std::shared_ptr<Node>;
    struct Node {
        T value;
        nodePtr next;
        Node(T);
    };
    nodePtr back;
    nodePtr front;
public:
    Queue();

    template<typename U> void push(U&& x);
    T pop();

    std::size_t size() const;
    bool empty() const;
};

#include "LinkedQueue.ipp"

#endif // LINKEDQUEUE_HPP_

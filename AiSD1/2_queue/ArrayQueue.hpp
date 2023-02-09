#ifndef ARRAYQUEUE_HPP_
#define ARRAYQUEUE_HPP_

#include <cstddef>

template<typename T>
class Queue {
    T* data;
    std::size_t capacity;

    std::size_t back;
    std::size_t front;
public:
    Queue(std::size_t = 16);
    ~Queue();

    template<typename U> void push(U&& x);
    T pop();

    std::size_t size() const;
    bool empty() const;
};

#include "ArrayQueue.ipp"

#endif // ARRAYQUEUE_HPP_

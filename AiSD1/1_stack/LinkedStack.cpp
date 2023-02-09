#include "LinkedStack.hpp"

#include <iostream>
#include <stdexcept>

Stack::Stack(std::size_t N) :
    capacity{N}, count{0}, head{nullptr}
{}

Stack::Node::Node(int val, Stack::nodePtr p) :
    value{val}, prev{std::move(p)}
{}

void Stack::push(int x)
{
    if (capacity != 0 && count >= capacity) {
        throw std::out_of_range{ "maximal capacity of stack reached" };
    }
    head = std::make_unique<Node>(x, std::move(head));
    ++count;
}

int Stack::pop()
{
    if (empty()) {
        throw std::out_of_range{ "stack already empty" };
    }
    int val = head->value;
    head = std::move(head->prev);
    --count;
    return val;
}

bool Stack::empty() const
{
    return !head;
}

std::size_t Stack::size() const
{
    return count;
}

#ifndef ARRAYSTACK_HPP_
#define ARRAYSTACK_HPP_

#include <cstddef>

#include "TmplStack.hpp"

class Stack : public tmpl::Stack<int,1> {
public:
    Stack(const std::size_t N);
    ~Stack();

    // The interface of this class is to be similar to `tmpl::Stack`
    // with the exception of `top()` method, thus deletion.
    int& top() = delete;
};

#endif // ARRAYSTACK_HPP_

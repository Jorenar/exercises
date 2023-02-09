#ifndef STACK_HPP_
#define STACK_HPP_

#ifdef STACK_IMPLEMENTED
#  error Stack class already implemented
#endif

#include <cstddef>

namespace tmpl {

template<typename T, const std::size_t N>
class Stack {
protected:
    T array[N];
    T* data;
    std::size_t idx;
    const std::size_t capacity;

public:
    Stack(std::size_t = N);

    template<typename U> void push(U&& x);
    T pop();

    T& top() const;
    std::size_t size() const;
    bool empty() const;
};

} // namespace tmpl

#include "TmplStack.ipp"

#ifndef ARRAYSTACK_HPP_
using namespace tmpl;
#endif

#define STACK_IMPLEMENTED

#endif // STACK_HPP_

#ifndef STACK_HPP_
#  error Template implementation file should only be included from corresponding header file
#endif // STACK_HPP_
#define STACK_IPP_

#include <stdexcept>

namespace tmpl {

#define IPP(X)     IPP_ ## X
#define IPP_TMPL   template<typename T, const std::size_t N>
#define IPP_STACK  Stack<T,N>

IPP(TMPL)
IPP(STACK)::Stack(std::size_t n) :
    array{0}, data{array}, idx{0}, capacity{n}
{}

IPP(TMPL)
template<typename U>
void IPP(STACK)::push(U&& x)
{
    if (idx >= capacity) {
        throw std::out_of_range{ "maximal capacity of stack reached" };
    }
    data[++idx] = std::forward<U>(x);
}

IPP(TMPL)
T IPP(STACK)::pop()
{
    if (empty()) {
        throw std::out_of_range{ "stack already empty" };
    }
    return data[idx--];
}

IPP(TMPL)
T& IPP(STACK)::top() const
{
    if (empty()) {
        throw std::out_of_range{ "stack empty" };
    }
    return data[idx];
}

IPP(TMPL)
std::size_t IPP(STACK)::size() const
{
    return idx;
}

IPP(TMPL)
bool IPP(STACK)::empty() const
{
    return !idx;
}

} // namespace tmpl

#undef IPP
#undef IPP_TMPL
#undef IPP_STACK

// vim: fdl=1

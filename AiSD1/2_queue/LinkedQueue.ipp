#ifndef LINKEDQUEUE_HPP_
#  error Template implementation file should only be included from corresponding header file
#endif // LINKEDQUEUE_HPP_

#include <stdexcept>

#define IPP(X)     IPP_ ## X
#define IPP_TMPL   template<typename T>
#define IPP_QUEUE  Queue<T>

IPP(TMPL)
IPP(QUEUE)::Queue() :
    count{0}, back{nullptr}, front{nullptr}
{}

IPP(TMPL)
IPP(QUEUE)::Node::Node(T val) :
    value{val},
    next{nullptr}
{}

IPP(TMPL)
template<typename U>
void IPP(QUEUE)::push(U&& x)
{
    auto temp = std::make_shared<Node>(std::forward<U>(x));
    if (front) {
        front->next = temp;
    }
    front = temp;

    if (!back) {
        back = front;
    }

    ++count;
}

IPP(TMPL)
T IPP(QUEUE)::pop()
{
    if (empty()) {
        throw std::out_of_range{ "queue empty" };
    }
    T ret = std::move(back->value);
    back = std::move(back->next);
    --count;
    return ret;
}

IPP(TMPL)
std::size_t IPP(QUEUE)::size() const
{
    return count;
}

IPP(TMPL)
bool IPP(QUEUE)::empty() const
{
    return !count;
}

#undef IPP
#undef IPP_TMPL
#undef IPP_QUEUE

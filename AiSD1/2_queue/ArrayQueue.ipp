#ifndef ARRAYQUEUE_HPP_
#  error Template implementation file should only be included from corresponding header file
#endif // ARRAYQUEUE_HPP_

#include <stdexcept>

#define IPP(X)     IPP_ ## X
#define IPP_TMPL   template<typename T>
#define IPP_QUEUE  Queue<T>

IPP(TMPL)
IPP(QUEUE)::Queue(std::size_t n) :
    capacity{n}, back{0}, front{0}
{
    data = new T[n];
}

IPP(TMPL)
IPP(QUEUE)::~Queue()
{
    delete [] data;
}

IPP(TMPL)
template<typename U>
void IPP(QUEUE)::push(U&& x)
{
    if (size() >= capacity) {
        throw std::out_of_range{ "maximal capacity of queue reached" };
    }

    data[front] = std::forward<U>(x);

    ++front;
    if (front >= capacity) {
        front = 0;
    }
}

IPP(TMPL)
T IPP(QUEUE)::pop()
{
    if (empty()) {
        throw std::out_of_range{ "queue empty" };
    }

    auto ret = data[back];

    ++back;
    if (back >= capacity) {
        back = 0;
    }

    return ret;
}

IPP(TMPL)
std::size_t IPP(QUEUE)::size() const
{
    return (front - back);
}

IPP(TMPL)
bool IPP(QUEUE)::empty() const
{
    return (front == back);
}

#undef IPP
#undef IPP_TMPL
#undef IPP_QUEUE

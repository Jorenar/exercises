#ifndef CURSORLIST_HPP_
#  error Template implementation file should only be included from corresponding header file
#endif

#include <stdexcept>

template<typename T, std::size_t N>
List<T,N>::List() : root{0}, terminator{N+1}
{
    clear();
}

template<typename T, std::size_t N>
void List<T,N>::clear()
{
    spare = 1;
    for (std::size_t i = spare; i < N; ++i) {
        data[i].next = i+1;
    }

    data[root].next = terminator;

    count = 0;
}

template<typename T, std::size_t N>
template<typename U>
void List<T,N>::push_front(U&& x)
{
    insert(0, std::forward<U>(x));
}

template<typename T, std::size_t N>
template<typename U>
void List<T,N>::push_back(U&& x)
{
    insert(count, std::forward<U>(x));
}

template<typename T, std::size_t N>
template<typename U>
void List<T,N>::insert(std::size_t n, U&& x)
{
    if (count >= N) {
        throw std::out_of_range{ "maximum capaticy exceeded" };
    }

    if (n > count) {
        throw std::out_of_range{ "no element with index " + std::to_string(n) };
    }

    auto pIdx = root;
    for (std::size_t i = 0; i < n; ++i) {
        pIdx = data[pIdx].next;
    }

    auto idx = spare;
    spare = data[spare].next;

    data[idx] = { std::forward<U>(x), data[pIdx].next };
    data[pIdx].next = idx;

    ++count;
}

template<typename T, std::size_t N>
T List<T,N>::pop_front()
{
    return erase(0);
}

template<typename T, std::size_t N>
T List<T,N>::pop_back()
{
    return erase(count-1);
}

template<typename T, std::size_t N>
T List<T,N>::erase(std::size_t n)
{
    if (empty()) {
        throw std::out_of_range{ "list empty" };
    }

    if (n >= count) {
        throw std::out_of_range{ "no element with index " + std::to_string(n) };
    }

    auto pIdx = root;
    for (std::size_t i = 0; i < n; ++i) {
        pIdx = data[pIdx].next;
    }
    auto idx = data[pIdx].next;

    data[pIdx].next = data[idx].next;
    data[idx].next = spare;
    spare = idx;

    --count;
    return data[idx].value;
}

template<typename T, std::size_t N>
std::size_t List<T,N>::remove(T x)
{
    std::size_t c = 0;
    signed_size_t idx;
    while ((idx = find(x)) >= 0) {
        ++c;
        erase(idx);
    }
    return c;
}

template<typename T, std::size_t N>
std::size_t List<T,N>::size() const
{
    return count;
}

template<typename T, std::size_t N>
bool List<T,N>::empty() const
{
    return !count;
}

template<typename T, std::size_t N>
typename List<T,N>::signed_size_t List<T,N>::find(T x) const
{
    signed_size_t i = 0;
    for (auto idx = data[root].next; idx != terminator; idx = data[idx].next) {
        if (data[idx].value == x) {
            return i;
        }
        ++i;
    }
    return -1;
}

template<typename T, std::size_t N>
bool List<T,N>::replace(T x, T y)
{
    for (auto idx = data[root].next; idx != terminator; idx = data[idx].next) {
        if (data[idx].value == x) {
            data[idx].value = y;
            return true;
        }
    }
    return false;
}


#ifdef DEBUG
#include <iostream>

template<typename T, std::size_t N>
void List<T,N>::print() const
{
    std::cerr << "List:";
    for (auto idx = data[root].next; idx != terminator; idx = data[idx].next) {
        std::cerr << ' ' << data[idx].value;
    }
    std::cerr << '\n';
}

#endif

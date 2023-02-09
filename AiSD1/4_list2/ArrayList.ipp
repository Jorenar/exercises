#ifndef ARRAYLIST_HPP_
#  error Template implementation file should only be included from corresponding header file
#endif // ARRAYLIST_HPP_

#include <stdexcept>

template<typename T, std::size_t N>
List<T,N>::List() : count{0} {}

template<typename T, std::size_t N>
template<typename U>
void List<T,N>::insert(std::size_t n, U&& x)
{
    if (count >= N) {
        throw std::out_of_range{ "maximum capaticy exceeded" };
    }

    for (std::size_t i = count+1; i > n; --i) {
        data[i] = data[i-1];
    }
    data[n] = std::forward<U>(x);
    ++count;
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
T List<T,N>::erase(std::size_t n)
{
    if (n >= count) {
        throw std::out_of_range{ "there isn't as many elements in list" };
    }

    auto ret = data[n];
    --count;
    for (std::size_t i = n; i < count; ++i) {
        data[i] = data[i+1];
    }
    return ret;
}

template<typename T, std::size_t N>
T List<T,N>::pop_back()
{
    return erase(count-1);
}

template<typename T, std::size_t N>
T List<T,N>::pop_front()
{
    return erase(0);
}

template<typename T, std::size_t N>
typename List<T,N>::signed_size_t List<T,N>::find(T x) const
{
    for (signed_size_t i = 0; i < count; ++i) {
        if (data[i] == x) {
            return i;
        }
    }
    return -1;
}

template<typename T, std::size_t N>
std::size_t List<T,N>::remove(T x)
{
    std::size_t c = 0;
    for (std::size_t i = 0; i < count; ++i) {
        if (data[i] == x) {
            ++c;
            erase(i);
            --i; // index correction to accommodate increment
        }
    }
    return c;
}

template<typename T, std::size_t N>
void List<T,N>::clear()
{
    count = 0;
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
bool List<T,N>::replace(T x, T y)
{
    for (std::size_t i = 0; i < count; ++i) {
        if (data[i] == x) {
            data[i] = y;
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
    for (std::size_t i = 0; i < count; ++i) {
        std::cerr << ' ' << data[i];
    }
    std::cerr << '\n';
}

#endif

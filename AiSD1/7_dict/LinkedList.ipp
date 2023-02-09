#ifndef LINKEDLIST_HPP_
#  error Template implementation file should only be included from corresponding header file
#endif

#include <stdexcept>

template<typename T>
List<T>::List() :
    count{0}, guard{new Node}
{
    guard->prev = guard->next = guard;
}

template<typename T>
List<T>::~List()
{
    clear();
    delete guard;
}

template<typename T>
void List<T>::clear()
{
    auto N = guard->prev;
    while (N != guard) {
        guard->prev = N->next;
        delete N;
        N = guard->prev;
    }
    count = 0;
}

template<typename T>
List<T>::Node::Node(T val, Node* p, Node* n) :
    value{val}, prev{p}, next{n}
{}

template<typename T>
typename List<T>::Node* List<T>::getNodeFromIdx(std::size_t n) const
{
    if (empty()) {
        return guard;
    }

    if (n >= count) {
        throw std::out_of_range{ "there isn't as many elements in list" };
    }

    auto temp = guard->prev;
    auto d = 1;
    std::size_t start = 0;

    if (n > count/2) {
        d = -1;
        start = count-1;
        temp = guard->next;
    }

    for (std::size_t i = start; i != n; i += d) {
        temp = (d == 1) ? temp->next : temp->prev;
    }

    return temp;
}

template<typename T>
template<typename U>
void List<T>::push_front(U&& x)
{
    auto temp = new Node(std::forward<U>(x), guard->next, guard);
    guard->next->next = temp;
    guard->next = temp;
    if (guard->prev == guard) {
        guard->prev = temp;
    }
    ++count;
}

template<typename T>
template<typename U>
void List<T>::push_back(U&& x)
{
    insert(0, std::forward<U>(x));
}

template<typename T>
template<typename U>
void List<T>::insert(std::size_t i, U&& x)
{
    auto g = getNodeFromIdx(i);

    auto temp = new Node(std::forward<U>(x), g->prev, g);
    g->prev->prev = temp;
    g->prev = temp;
    if (g == guard && guard->next == guard) {
        guard->next = temp;
    }

    ++count;
}

template<typename T>
T List<T>::pop_front()
{
    return erase(count-1);
}

template<typename T>
T List<T>::pop_back()
{
    return erase(0);
}

template<typename T>
T List<T>::eraseNode(Node* N)
{
    auto pn = (N->prev == guard) ? &(guard->prev) : &(N->prev->next);
    *pn = N->next;

    auto np = (N->next == guard) ? &(guard->next) : &(N->next->prev);
    *np = N->prev;

    auto ret = N->value;
    delete N;
    --count;
    return ret;
}

template<typename T>
T List<T>::erase(std::size_t i)
{
    auto temp = getNodeFromIdx(i);
    if (temp == guard) {
        throw std::out_of_range{ "list empty" };
    }
    return eraseNode(temp);
}

template<typename T>
std::size_t List<T>::remove(T x)
{
    std::size_t c = 0;
    for (auto N = guard->prev; N != guard; /* N = N->next */) {
        auto temp = N->next;
        if (N->value == x) {
            ++c;
            eraseNode(N);
        }
        N = temp;
    }
    return c;
}

template<typename T>
std::size_t List<T>::size() const
{
    return count;
}

template<typename T>
bool List<T>::empty() const
{
    return !count;
}

template<typename T>
int List<T>::find(T x) const
{
    auto temp = guard->prev;
    for (std::size_t i = 0; i < count; ++i) {
        if (temp->value == x) {
            return static_cast<int>(i);
        }
        temp = temp->next;
    }
    return -1;
}

template<typename T>
bool List<T>::replace(T x, T y)
{
    auto temp = guard->next;
    for (std::size_t i = 0; i < count; ++i) {
        if (temp->value == x) {
            temp->value = y;
            return true;
        }
        temp = temp->prev;
    }
    return false;
}


#ifdef DEBUG
#include <iostream>

template<typename T>
void List<T>::print() const
{
    std::cerr << "List:";
    for (auto temp = guard->prev; temp != guard; temp = temp->next) {
        std::cerr << ' ' << temp->value;
    }
    std::cerr << '\n';
}

#endif

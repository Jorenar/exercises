#ifndef CURSORLIST_HPP_
#define CURSORLIST_HPP_

#include <array>
#include <cstddef>
#include <type_traits>

template<typename T, std::size_t N>
class List {
    struct Node {
        T value;
        std::size_t next;
    };

    std::size_t count;
    std::array<Node, N+1> data;

    const std::size_t root; // (dummy) first element in array
    const std::size_t terminator;
    std::size_t spare;

public:
    List();
    ~List() = default;

    template<typename U> void insert(std::size_t i, U&& x);

    template<typename U> void push_front(U&& x);
    template<typename U> void push_back(U&& x);

    T pop_front();
    T pop_back();

    void clear();
    T erase(std::size_t i);
    std::size_t remove(T x);

    std::size_t size() const;
    bool empty() const;

    using signed_size_t = std::make_signed_t<std::size_t>;
    signed_size_t find(T x) const;

    bool replace(T, T); // see comment under `case 'R'` in LinkedList.cpp
                        // from previous exercise

#ifdef DEBUG
    void print() const;
#endif

};

#include "CursorList.ipp"

#endif // CURSORLIST_HPP_

// vim: fdl=2

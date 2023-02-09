#ifndef LINKEDLIST_HPP_
#define LINKEDLIST_HPP_

#include <cstddef>

template<typename T>
class List {
    struct Node {
        T value;
        Node* prev;
        Node* next;
        Node(T = {}, Node* p = nullptr, Node* n = nullptr);
    };

    std::size_t count;
    Node* guard; // could be a regular object instead of a pointer... but consistency!

    Node* getNodeFromIdx(std::size_t) const;
    T eraseNode(Node*);

public:
    List();
    ~List();

    template<typename U>
    void insert(std::size_t i, U&& x);

    template<typename U> void push_front(U&& x);
    template<typename U> void push_back(U&& x);

    T pop_front();
    T pop_back();

    void clear();
    T erase(std::size_t i);
    std::size_t remove(T x);

    std::size_t size() const;
    bool empty() const;
    int find(T x) const;

    bool replace(T, T); // see comment under `case 'R'` in LinkedList.cpp

#ifdef DEBUG
    void print() const;
#endif

};

#include "LinkedList.ipp"

#endif // LINKEDLIST_HPP_

// vim: fdl=2

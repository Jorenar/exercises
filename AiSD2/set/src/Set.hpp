#ifndef SET_HPP_
#define SET_HPP_

#include "RedBlackTree.hpp"

template<typename T>
class Set : public RedBlackTree<T> {
    using Base = RedBlackTree<T>;
    using Node = typename Base::Node;
public:
    void insert(T v);
    bool isMember(T v) const;
    T pop();

    Set* intersection(Set*) const;
    Set* difference(Set*) const;
    Set* unionWith(Set*) const;
};

#include "Set.ipp"

#endif // SET_HPP_

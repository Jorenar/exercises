#ifndef DICT_HPP_
#define DICT_HPP_

#include <array>
#include <utility>

#include "LinkedList.hpp"

template<typename K, typename V>
class Dict {
    using Pair = std::pair<K, V>;
    std::array<List<Pair>, 1024> data;
    std::size_t count;
public:
    Dict();
    void clear();
    bool insert(const Pair& p);
    bool find(const K& k);
    V& operator [](const K& k);
    bool erase(const K& k);
    std::size_t size() const;
    bool empty() const;
    void buckets() const;
};

#include "Dict.ipp"

#endif // DICT_HPP_

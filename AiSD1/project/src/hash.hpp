#ifndef HASH_HPP_
#define HASH_HPP_

#include <cstddef>
#include <string>

template<typename K>
std::size_t hash(const K&)
{
    return 0;
}

template<>
std::size_t hash(const uint16_t& k)
{
    return k % 1024;
}

template<>
std::size_t hash(const std::string& k)
{
    std::size_t h = 0;
    for (auto c: k) {
        h += c; // dead simple
    }
    return h % 1024;
}

#endif // HASH_HPP_

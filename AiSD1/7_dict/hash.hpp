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
std::size_t hash(const std::string& k)
{
    std::size_t h = 29;
    for (auto c: k) {
        h += static_cast<std::size_t>((c*71 >> 2) ^ (k[0]*53));
    }
    return h % 1024;
}

#endif // HASH_HPP_

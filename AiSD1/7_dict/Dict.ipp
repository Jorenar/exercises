#ifndef DICT_HPP_
#  error Template implementation file should only be included from corresponding header file
#endif // DICT_HPP_

#define IPP_TPL template<typename K, typename V>

#include <iostream>
#include <stdexcept>

#include "hash.hpp"

IPP_TPL Dict<K,V>::Dict() :
    count {0}
{}

IPP_TPL void Dict<K,V>::clear()
{
    for (auto& d: data) {
        d.clear();
    }
    count = 0;
}

IPP_TPL bool Dict<K,V>::insert(const Pair& p)
{
    if (find(p.first)) {
        return false;
    }

    auto h = hash(p.first);

    data[h].push_back(p);
    ++count;
    return true;
}

IPP_TPL bool Dict<K,V>::find(const K& k)
{
    auto h = hash(k);

    if (h >= data.size()) {
        return false;
    }

    auto dg = data[h].guard;
    for (auto N = dg->prev; N != dg; N = N->next) {
        if (N->value.first == k) {
            return true;
        }
    }

    return false;
}

IPP_TPL V& Dict<K,V>::operator [](const K& k)
{
    if (!this->find(k)) {
        this->insert({ k, {} });
    }

    auto dg = data[hash(k)].guard;
    for (auto N = dg->prev; N != dg; N = N->next) {
        if (N->value.first == k) {
            return N->value.second;
        }
    }

    throw std::runtime_error{ "" };
}

IPP_TPL bool Dict<K,V>::erase(const K& k)
{
    auto h = hash(k);

    if (h >= data.size()) {
        return false;
    }

    auto d = data[h];
    auto dg = d.guard;
    for (auto N = dg; N != dg; N = N->next) {
        // no need for `temp`, bc of early return
        if (N->value.first == k) {
            d.eraseNode(N);
            --count;
            return true;
        }
    }

    return false;
}

IPP_TPL std::size_t Dict<K,V>::size() const
{
    return count;
}

IPP_TPL bool Dict<K,V>::empty() const
{
    return !count;
}

IPP_TPL void Dict<K,V>::buckets() const
{
    std::size_t min = SIZE_MAX;
    std::size_t max = 0;

    std::size_t cl = 0;

    std::size_t S = 0;

    for (auto& d: data) {
        if (d.empty()) { continue; }

        auto s = d.size();
        S += s;
        if (s > max) { max = s; }
        if (s < min) { min = s; }
        ++cl;
    }

    std::cout << "# "
              << size() << " "
              << cl << " "
              << min << " "
              << max << '\n';

#ifdef DEBUG
    std::cerr << "Average (floored) bucket size: " << S/cl << std::endl;
#endif
}

#undef IPP_TPL

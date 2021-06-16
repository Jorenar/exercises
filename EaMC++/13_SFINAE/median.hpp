#pragma once

#include <algorithm>
#include <iterator>
#include <type_traits>

namespace helpers {

template<typename C>
double doMedian(C set, std::bidirectional_iterator_tag)
{
    set.sort();

    auto it = set.begin();

    size_t n = set.size();

    for (size_t i = 1-n%2; i < n / 2; ++i) {
        ++it;
    }

    if (n % 2 == 0) {
        return static_cast<double>(*it + *(++it)) / 2;
    }
    else {
        return *it;
    }
}

template<typename C>
double doMedian(C set, std::random_access_iterator_tag)
{
    sort(set.begin(), set.end());
    size_t n = set.size();
    auto m = set.begin() + n/2 - 1 + n%2;

    if (n % 2 == 0) {
        return static_cast<double>(*m + *(m+1)) / 2;
    }
    else {
        return *m;
    }
}

int foo();

} // namespace helpers

template<typename C>
double median(C set)
{
    using It_t = decltype(set.begin());
    return helpers::doMedian(set, typename std::iterator_traits<It_t>::iterator_category());
}

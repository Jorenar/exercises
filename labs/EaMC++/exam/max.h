#pragma once

template<typename iterator, typename function>
iterator max_arg(iterator first, iterator last, function f)
{
    auto max  = first;
    auto fMax = f(*max);
    iterator x = first; // Here, instead in `for` loop, for security. There is
    ++x;                // no telling, what function `f` can do with those pointers
    for (; x != last; ++x) {
        auto t = f(*x);
        if (t > fMax) {
            max  = x;
            fMax = t;
        }
    }
    return max;
}

// vim: ft=cpp

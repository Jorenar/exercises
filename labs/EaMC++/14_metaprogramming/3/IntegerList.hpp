#pragma once

#include <sstream>

template<int...>
struct IntegerList {
    template<int... A>
    friend std::ostream& operator <<(std::ostream&, const IntegerList<A...>&);
};

template<int... Args>
std::ostream& operator <<(std::ostream& out, const IntegerList<Args...>& obj)
{
    auto f = [&](auto x) { out << x << " "; };
    (..., f(Args));
    return out;
}

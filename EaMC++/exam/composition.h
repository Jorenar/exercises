#pragma once

#include <type_traits>
#include <utility>

template<typename F, typename G>
class Composition {
    F f;
    G g;
public:
    Composition(F f, G g) : f(f), g(g) {}

    template<typename... Args>
    auto operator ()(Args&&... a)
    {
        return g(f(std::forward<Args>(a)...));
    }

};

template<typename F, typename G>
Composition<F,G> make_composition(F f, G g)
{
    return Composition<F,G>(f,g);
}

// vim: ft=cpp

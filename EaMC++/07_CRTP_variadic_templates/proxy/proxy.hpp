#pragma once

// C++11

#include <iostream>
#include <utility>

void showTypes(int) {}

template<typename T, typename... Args>
void showTypes(int n, T t, Args&& ... args)
{
    std::cout << " " << n << " > " << typeid(t).name() << " " << t << std::endl;
    showTypes(++n, std::forward<Args>(args)...);
}

template<typename... Args>
inline void showTypes(Args&& ... args)
{
    showTypes(1, std::forward<Args>(args)...);
}

template<typename... Args>
inline void showNames(Args&& ... args)
{
    showTypes(1, std::forward<Args>(args)...);
}

template<typename F>
class Proxy {
  public:
    Proxy(F f) : f(f) {}

    template<typename... Args>
    auto operator ()(Args&& ... args)
    {
        std::cout << std::endl << "Proxy" << std::endl;
        showTypes(1, std::forward<Args>(args) ...);
        return f(std::forward<Args>(args)...);
    }

  private:
    F f;
};

template<typename F>
Proxy<F> make_proxy(F f)
{
    Proxy<F> temp(f);
    return temp;
}

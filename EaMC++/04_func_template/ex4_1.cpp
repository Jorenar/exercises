#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

// A -------------------------

template<typename T>
T sqr(T x)
{
    return x*x;
}

template<>
std::string sqr<std::string>(std::string x)
{
    return x+x;
}

// B -------------------------

template<int N>
int mod(int x)
{
    return x % N;
}

template<>
int mod<0>(int x)
{
    return -x;
}

// C -------------------------

template<class Container>
void print(const Container& v)
{
    for (auto x: v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

// D -------------------------

template<class C, typename F>
C apply(const C& c, F f)
{
    C temp;
    std::transform(std::begin(c), std::end(c), std::back_inserter(temp), f);
    return temp;
}


// TESTS ---------------------

int main()
{

    // function template  sqr<T>
    cout << sqr(4) << endl;             // 16
    cout << sqr(14.5) << endl;          // 210.25
    cout << sqr(string("hey")) << endl; // heyhey

    // function template mod<N>
    cout << mod<5>(131) << endl;        // 1
    cout << mod<7>(131) << endl;        // 5

    // function template print
    std::vector<int> v = {1, 21, 34, 4, 15};
    print(v);                    // 1 21 34 4 15

    std::list<double> l = {1, 2.1, 3.2, 6.3};
    print(l);                    // 1 2.1 3.2 6.3

    // function template apply
    auto w = apply(v, sqr<int>);
    print(w);  // 1 441 1156 16 225

    auto w2 = apply(w, mod<5> );
    print(w2); // 1 1 1 1 0

    auto w3 = apply(w, mod<0> );
    print(w3); // -1 -441 -1156 -16 -225


    auto l2 = apply(l, sqr<double>);
    print(l2); // 1 4.41 10.24 39.69

    auto l3 = apply(l2, mod<5>);
    print(l3); // 1 4 0 4

    // function sin is overloaded, we need to cast it
    auto l4 = apply(l3, static_cast<double(*)(double)>(std::sin));
    print(l4); // 0.841471 -0.756802 0 -0.756802

    return 0;
}

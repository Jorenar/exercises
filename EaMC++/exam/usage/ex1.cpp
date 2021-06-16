#include <iostream>
#include <cmath>
#include "composition.h"

using namespace std;

int f(int a, int b, int c) {
    return a + b - c;
}

int g(int &a, int &b) {
    a++;
    b--;
    return a - b;
}

int main() {
    int a = 2, b = 3;
    Composition c(f, static_cast<int (*)(int)>( std::abs)); // c++17
    // Composition<int (*)(int, int, int), int (*)(int)> c(f, static_cast<int (*)(int)>( std::abs)); // c++14
    cout << c(a, b, 10) << endl;  // 5
    auto d = make_composition(g, [](int x) { return x * x; });
    cout << d(a, b) << endl;   // 1
    cout << d(a, b) << endl;   //9
    auto e = make_composition([](float x) { return sin(x) * 4; }, [](float x) { return (int) (x + 0.5); });
    cout << e(0.3) << endl;   //1
    cout << e(M_PI / 2) << endl; //4
    auto s = make_composition(
            [](const string &s, const string &s2) { return s + s2; },
            [](const string &s) { return atoi(s.c_str()); }
    );
    int result = s("12"s, "345"s);
    cout << result << endl; // 12345

    return 0;
}

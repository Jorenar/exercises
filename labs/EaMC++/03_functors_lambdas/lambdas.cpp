#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <cassert>
#include <numeric>
#include <cmath>
#include <type_traits>
using namespace std;

void print(const std::vector<int>& v)
{
    for ( auto x  : v) { cout << x << " "; }
    cout << endl;
}

int main()
{
    std::vector<int> v = {256, 64, 16*3, 16*9, 16, 8*7, 9, 3, 1, 6, 2, 5};
    print(v);

    int center = 50;

    // ( 1 )
    std::sort(v.begin(), v.end(), [&center](auto a, auto b) {
        return abs(center-a) < abs(center-b) ? true : false;
        });

    print(v);

    // ( 2 )   -- I really don't know how does this ordering works
    auto sharkovsky = [](auto a, auto b) {
        if (a == 1 || b == 1) {
            return a < b;
        }
        else if (a%2 && b%2) {
            return b < a;
        }
        else if (!(a%2) && b%2) {
            return true;
        }
        else if (a%2 && !(b%2)) {
            return false;
        }
        else {  // two evens
            if ( log2(a) == floor(log2(a)) && log2(b) == floor(log2(b)) ) {
                return a < b;
            }
            else if ( log2(a) == floor(log2(a)) && log2(b) != floor(log2(b)) ) {
                return true;
            }
            else if ( log2(a) != floor(log2(a)) && log2(b) == floor(log2(b)) ) {
                return false;
            }
            else {
                if ( (a/2)%2 && !((b/2)%2) ) {
                    return false;
                }
                else if ( !((a/2)%2) && (b/2)%2 ) {
                    return true;
                }
                else {
                    if ( floor(log(a)) < floor(log(b)) ) {
                        return false;
                    }
                    else if ( floor(log(a)) > floor(log(b)) ) {
                        return true;
                    } else {
                        return a > b;
                    }
                }
            }
        }
    };

    assert(sharkovsky(1,2));
    assert(sharkovsky(2,4));
    assert(sharkovsky(64,256));
    assert(sharkovsky(256,256*3));
    assert(sharkovsky(256*9,256*5));
    assert(sharkovsky(256*3,64*9));
    assert(!sharkovsky(1,1));
    assert(!sharkovsky(4,2));
    assert(!sharkovsky(256,64));
    assert(!sharkovsky(256*3,256));
    assert(!sharkovsky(256*5,256*9));
    assert(!sharkovsky(64*9,256*3));

    std::sort(v.begin(), v.end(), sharkovsky);
    print(v);

    srand(2019);
    int a = 0, b = 40;

    // ( 3 )
    auto generator = [&]() { return std::rand()%(b+(a < 0 ? -a : 0)) + a; };

    std::generate(v.begin(), v.end(), generator);
    print(v);

    a = 100, b = 200;
    std::generate(v.begin(), v.end(), generator);
    print(v);

    a = -10;
    b=10;

    // ( 4 )
    auto evenGenerator = [=]() -> int {
        return ((std::rand()%(b+(a < 0 ? -a : 0)) + a)/2)*2;
    };

    std::generate(v.begin(), v.end(), evenGenerator);
    print(v);

    v.resize(20);
    a = 0;
    b=100;
    std::generate(v.begin(), v.end(), evenGenerator);
    print(v);

    // ( 5 )
    auto l1_norm = [](auto x) {
        return std::accumulate(begin(x), end(x), 0.0, [](auto a, auto b) {
            return a + fabs(b);
            });
    };

    cout << l1_norm(v) << endl;

    vector<double> m = { 1.4, 2.4, -2.4, -4.2, -43.3 };
    cout << l1_norm(m) << endl;

    list<double> l(m.begin(), m.end());
    cout << l1_norm(l) << endl;

    // ( 6 )
    auto wielomian = [](auto&& A, int&& n) {
        return [&A, &n](auto x) {
            double w = 0;
            for (int i = 0; i <= n; i++) {
                w += A[i] * pow(x, i);
            }
            return w;
        };
    };


    // I had to change `a` to `a2`, because `a` was previously declared
    double a2[] = {1, 2, 3, 4, 5};
    auto w1  = wielomian(a2, 4);
    cout << w1(1.0) << " " << w1(0.0) << " " << w1(2.0) << endl;

    auto w2  = wielomian(a2, 2);
    cout << w2(1.0) << " " << w2(0.0) << " " << w2(2.0) << endl;

    return 0;
}


/**
  Expected output (or similar):
  256 64 48 144 16 56 9 3 1 6 2 5
  48 56 64 16 9 6 5 3 2 1 144 256
  1 2 16 64 256 144 48 56 6 9 5 3
  11 33 7 4 40 20 36 27 4 38 31 18
  142 135 106 164 160 189 152 196 156 102 198 114
  0 -2 -6 -8 -2 -10 -2 -4 -4 0 -8 0
  -6 -2 -4 -8 8 -6 0 -4 8 -2 6 8 -8 -8 2 10 10 -6 6 2
  114
  53.7
  53.7
  15 1 129
  6 1 17
  */

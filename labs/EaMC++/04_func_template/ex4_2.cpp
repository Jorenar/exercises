#include <cstring>
#include <iostream>

using namespace std;

template<typename T>
int compare(T a, T b)
{
    if (a < b) {
        return 1;
    }
    else if (b < a) {
        return -1;
    }
    else {
        return 0;
    }
}

template<typename T>
int compare(T* a, T* b)
{
    if (*a < *b) {
        return 1;
    }
    else if (*b < *a) {
        return -1;
    }
    else {
        return 0;
    }
}

template<>
int compare<>(const char* a, const char* b)
{
    int n = strcmp(a, b);
    if (n > 0) {
        return -1;
    }
    else if (n < 0) {
        return 1;
    }
    else {
        return 0;
    }
}


struct Rational {
    int nominator=0, denominator=1;
    friend bool operator<(const Rational& a, const Rational& b)
    {
        return a.nominator*b.denominator < b.nominator*a.denominator;
    }
};

int main()
{
    int a = 1, b=-6;
    float  y= 1.0 + 1e20 - 1e20, x = 1.0;
    Rational p{2}, q{1,4}, r{8,4};
    cout << "values\n";
    cout << compare(a,b) << " " << compare(b,a) << " " << compare(a,a) << endl;
    cout << compare(x,y) << " " << compare(y,x) << " " << compare(x,x) << endl;
    cout << compare(p,q) << " " << compare(q,p) << " " << compare(p,r) << endl;
    cout << "pointers\n";
    cout << compare(&a,&b) << " " << compare(&b,&a) << " " << compare(&a,&a) << endl;
    cout << compare(&x,&y) << " " << compare(&y,&x) << " " << compare(&x,&x) << endl;
    cout << compare(&p,&q) << " " << compare(&q,&p) << " " << compare(&p,&r) << endl;

    const char* s  = "Alpha", *t="Alfa", *t2 = "Alfa";
    cout << "C-strings\n";
    cout << compare(s,t) << " " << compare(t,s) << " " << compare(t,t)
        << " " << compare(t, t2) << " " << compare(t, "Beta") << endl;

    return 0;
}

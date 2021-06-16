#include <iostream>
#include "String.hpp"

using namespace std;

int main()
{
    String a("hi");
    String b;
    const String c = a;     // no copy
    String d = a+b;         // no copy
    a[0] = 'l';             // copy
    a[1] = 'l';             // no copy
    c[0] = 'l';
    d = c+a;                // copy elision
    cout << c << " " << d << endl;    // hi hill   (no copy)
    cout << c[0] << endl;             // l         (no copy)

    return 0;
}

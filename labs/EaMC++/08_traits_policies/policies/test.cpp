#include <iostream>
#include "Vector.h"

using  namespace std;

int main() {
    int value = 5;
    {  /// sets coordinates to zero and checks indices
        using Vect = Vector<double, 3, SafePolicy>;
        Vect a{};
        a.set(1, -1);              // OK
        cout << a << endl;         // 0 -1 0
        //a.set(-1, 1.);             // Exception
        //cout << a.get(3) << endl;  // Exception
        //Vect b{1, 2, 3, 4};        // Exception
    }
    { /// does not initialize by default and does not check indices
        using Vect = Vector<double, 3, FastPolicy>;
        Vect a{};
        a.set(1, -1);              // OK
        cout << a << endl;         // Unspecified (random values on first and third coordinate)
        a.set(-1, 1.);             // Unspecified
        cout << value << endl;     // value possibly changed by the previous line
        cout << a.get(3) << endl;  // Unspecified
        Vect b{1, 2, 3, 4};        // OK: it makes copy of only first three values
    }
    { /// initializes to zero by default but does not check indices
        using Vect = Vector<double, 3, InitFastPolicy>;
        Vect a{};
        a.set(1, -1);              // OK
        cout << a << endl;         // OK: 0 -1 0
        a.set(-1, 1.);             // Unspecified
        cout << value << endl;     // value possibly changed by the previous line
        cout << a.get(3) << endl;  // Unspecified
        Vect b{1, 2, 3, 4};        // OK: it makes copy of only first three values
        std::cout << b << std::endl;
    }
    return 0;
}

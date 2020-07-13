#include <iostream>
#include "max.h"
#include <vector>
using namespace std;

int main() {
    std::vector<int> v{1,2,3,10,4,5,6,17,3};
    auto i = max_arg(v.begin(), v.end(), [](int x){return x;});
    cout << *i << endl;  // 17
    auto i2 = max_arg(v.begin(), i, [](int x){return x;});
    cout << *i2 << endl;  // 10
    auto i3 = max_arg(v.begin(), v.end(), [](int x){return -x;});
    cout << *i3 << endl;  // 1
    auto i4 = max_arg(v.begin(), v.end(), [](int x){return -(x-4)*(x-6);});
    cout << *i4 << endl;  // 5
    return 0;
}


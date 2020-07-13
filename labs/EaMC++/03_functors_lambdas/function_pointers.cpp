#include <cmath>
#include <iostream>

using namespace std;

/// Computes n-th root of x
double sqrtn(int n, double x)
{
    return exp( log(x) / n );
}

double power(double x, double y)
{
    return exp( log(x) * y );
}

template <typename F, typename G>
double function(int n, double y, double z, F f, G g)
{
    return (f(n,y) > z) ? g(z, y) : g(y, z);
}

int main()
{
    typedef double (*fp1_t)(int, double);
    typedef double (*fp2_t)(double, double);
    fp1_t fp1 = sqrtn;
    fp2_t fp2 = power;
    double (*fp3)(int, double, double, fp1_t, fp2_t) = function<fp1_t, fp2_t>;
    cout << fp3(2, 10, 3, fp1, fp2) << endl;
    cout << fp3(3, 10, 3, fp1, fp2) << endl;
    return 0;
}

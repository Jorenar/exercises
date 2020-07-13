#include <iostream>

/**
   Computes velocity in meters per seconds.
   @param distance  distance in meters
   @param time      time in seconds
   @return velocity in meters per seconds.
 */
double computeVelocity(double distance, double time)
{
    return distance / time;
}

// Distance {{{

constexpr long double operator "" _m(long double x)
{
    return x;
}

constexpr long double operator "" _km(long double x)
{
    return 1000 * x;
}

constexpr long double operator "" _cm(long double x)
{
    return x / 100;
}


constexpr long double operator "" _m(unsigned long long int x)
{
    return x;
}

constexpr long double operator "" _km(unsigned long long int x)
{
    return 1000.0 * x;
}

constexpr long double operator "" _cm(unsigned long long int x)
{
    return x / 100.0;
}

// distance }}}

// Time {{{

constexpr long double operator "" _s(long double x)
{
    return x;
}

constexpr long double operator "" _ms(long double x)
{
    return x / 1000;
}

constexpr long double operator "" _h(long double x)
{
    return 3600 * x;
}


constexpr long double operator "" _s(unsigned long long int x)
{
    return x;
}

constexpr long double operator "" _ms(unsigned long long int x)
{
    return x / 1000.0;
}

constexpr long double operator "" _h(unsigned long long int x)
{
    return 3600.0 * x;
}

// time }}}

int main()
{
    std::cout << computeVelocity(100_m, 5_s) << std::endl;     //20
    std::cout << computeVelocity(360_km, 2.0_h) << std::endl;  //50
    std::cout << computeVelocity(3.6_km, 0.02_h) << std::endl; //50
    std::cout << computeVelocity(250_cm, 2.5_ms) << std::endl; //1000
    return 0;
}

// vim: fen

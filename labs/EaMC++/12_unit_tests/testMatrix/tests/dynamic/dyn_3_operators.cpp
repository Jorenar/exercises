#define BOOST_TEST_MODULE Operators
#include "../init_testing.hpp"
#include "dynamicMatrix.h"

using DM = Matrix<int,0,0>;

BOOST_AUTO_TEST_CASE(add)
{
    DM a{::initList3x3};
    DM b{::initList3x3};
    auto c = a + b;
    int x = 1;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            BOOST_CHECK_EQUAL(c(i,j), 2*x++);
        }
    }
}

BOOST_AUTO_TEST_CASE(multiplication)
{
    DM a{::initList3x3};
    DM b{::initList3x3};
    auto c = a * b;
    int multipled[] = { 30,36,42, 66,81,96, 102,126,150 };
    int x = 0;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            BOOST_CHECK_EQUAL(c(i,j), multipled[x++]);
        }
    }
}

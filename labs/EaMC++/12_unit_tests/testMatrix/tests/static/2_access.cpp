#define BOOST_TEST_MODULE Access
#include "../init_testing.hpp"
#include "staticMatrix.h"

BOOST_AUTO_TEST_CASE_TEMPLATE(ONExONE, T, test_types)
{
    TestBracket<T,1,1> t;
    t.m(1,1) = 3;
    BOOST_CHECK_EQUAL(t.m(1,1), T{ 3 });
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ONExFIVE, T, test_types)
{
    TestBracket<T,1,5> t;
    t.m(1,3) = 3;
    BOOST_CHECK_EQUAL(t.m(1,3), T{ 3 });
    t.m(1,5) = 3111;
    BOOST_CHECK_EQUAL(t.m(1,5), T{ 3111 });
}

BOOST_AUTO_TEST_CASE_TEMPLATE(FIVExFIVE, T, test_types)
{
    TestBracket<T,5,5> t;
    t.m(1,3) = 3;
    BOOST_CHECK_EQUAL(t.m(1,3), T{ 3 });
    t.m(4,5) = 3111;
    BOOST_CHECK_EQUAL(t.m(4,5), T{ 3111 });
}

BOOST_AUTO_TEST_CASE(int_initList_3x3)
{
    M3 m(::initList3x3);
    int x = 1;
    for (int i = 1; i <= m.numberOfRows(); ++i) {
        for (int j = 1; j <= m.numberOfColumns(); ++j) {
            BOOST_CHECK_EQUAL(m(i,j), x++);
        }
    }
}

// vim: fen

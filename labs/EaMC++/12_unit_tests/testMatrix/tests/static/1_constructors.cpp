#define BOOST_TEST_MODULE Constructors
#include "../init_testing.hpp"
#include "staticMatrix.h"

BOOST_AUTO_TEST_SUITE(defaultConstructors);

BOOST_AUTO_TEST_CASE_TEMPLATE(ONExONE, T, test_types)
{
    TestConstructor<T,1,1>(" constructor of static 1x1 matrix");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(THREExTHREE, T, test_types)
{
    TestConstructor<T,3,3>(" constructor of static 3x3 matrix");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(ONExFIVE, T, test_types)
{
    TestConstructor<T,1,5>(" constructor of static 1x5 matrix");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(FIVExONE, T, test_types)
{
    TestConstructor<T,5,1>(" constructor of static 5x1 matrix");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(FIVExFIVE, T, test_types)
{
    TestConstructor<T,5,5>(" constructor of static 5x5 matrix");
}

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_CASE(initList)
{
    coutRedirect guard(output.rdbuf());
    M3 a{ ::initList3x3 };
    CHECK_OUTPUT(" constructor of static 3x3 matrix from initializer_list\n");
}

BOOST_AUTO_TEST_CASE(copy)
{
    M3 a;
    coutRedirect guard(output.rdbuf());
    auto b = a;
    CHECK_OUTPUT(" copy constructor of static matrix\n");
}

// vim: fen

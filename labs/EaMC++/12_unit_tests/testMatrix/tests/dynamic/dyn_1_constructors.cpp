#define BOOST_TEST_MODULE Constructors
#include "../init_testing.hpp"
#include "dynamicMatrix.h"

using DM = Matrix<int,0,0>;

BOOST_AUTO_TEST_CASE_TEMPLATE(defaultConstructors, T, test_types)
{
    coutRedirect guard(output.rdbuf());
    for (int i = 1; i <= 10; ++i) {
        for (int j = 1; j <= 10; ++j) {
            Matrix<T,0,0> foo(i,j);
            std::string msg = " constructor of dynamic " + std::to_string(i) +
                         "x" + std::to_string(j) + " matrix\n";
            CHECK_OUTPUT(msg);
            BOOST_CHECK_EQUAL(foo.numberOfRows(), i);
            BOOST_CHECK_EQUAL(foo.numberOfColumns(), j);
        }
    }
}

BOOST_AUTO_TEST_CASE(initList)
{
    coutRedirect guard(output.rdbuf());
    DM a{ ::initList3x3 };
    CHECK_OUTPUT(" constructor of dynamic 3x3 matrix from initializer_list\n");
}

BOOST_AUTO_TEST_CASE(copy)
{
    DM a(5,1);
    coutRedirect guard(output.rdbuf());
    DM b(a);
    CHECK_OUTPUT(" copy constructor of dynamic matrix\n");
}

// vim: fen

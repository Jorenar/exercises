#define BOOST_TEST_MODULE Misc
#include "init_testing.hpp"

BOOST_AUTO_TEST_CASE(constant)
{
    String a("abc");
    BOOST_CHECK_EQUAL(a[0], 'a');
    BOOST_CHECK_EQUAL(a[1], 'b');
    BOOST_CHECK_EQUAL(a[2], 'c');
    BOOST_CHECK_EQUAL(a[3], '\0');
}

BOOST_AUTO_TEST_CASE(ref)
{
    String a("aaa");
    char& x = a[1];
    x = 'A';
    BOOST_CHECK_EQUAL(a[0], 'a');
    BOOST_CHECK_EQUAL(a[1], 'A');
    BOOST_CHECK_EQUAL(a[2], 'a');
    BOOST_CHECK_EQUAL(a[3], '\0');
}

// vim: fen

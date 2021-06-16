#define BOOST_TEST_MODULE Constructors
#include "init_testing.hpp"

BOOST_AUTO_TEST_CASE( empty )
{
    String a;
    BOOST_CHECK_EQUAL(a[0], '\0');
}

BOOST_AUTO_TEST_CASE(emptyWithParam)
{
    String a(2);
    BOOST_CHECK_EQUAL(a[0], 'x');
    BOOST_CHECK_EQUAL(a[1], 'x');
    BOOST_CHECK_EQUAL(a[2], '\0');
}

BOOST_AUTO_TEST_CASE(cString)
{
    String a("test");
    BOOST_CHECK_EQUAL(a[0], 't');
    BOOST_CHECK_EQUAL(a[1], 'e');
    BOOST_CHECK_EQUAL(a[2], 's');
    BOOST_CHECK_EQUAL(a[3], 't');
    BOOST_CHECK_EQUAL(a[4], '\0');
}

BOOST_AUTO_TEST_CASE(self)
{
    String a("test");
    String b(a);
    BOOST_CHECK_EQUAL(b[0], 't');
    BOOST_CHECK_EQUAL(b[1], 'e');
    BOOST_CHECK_EQUAL(b[2], 's');
    BOOST_CHECK_EQUAL(b[3], 't');
    BOOST_CHECK_EQUAL(b[4], '\0');
}

// vim: fen

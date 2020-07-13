#define BOOST_TEST_MODULE Misc
#include "init_testing.hpp"

BOOST_AUTO_TEST_CASE(addingObjs)
{
    String a("abc");
    String b("ABC");
    String r = a + b;
    BOOST_REQUIRE(r[0] == a[0]);
    output << r;
    CHECK_OUTPUT("abcABC");
}

BOOST_AUTO_TEST_CASE(addingObjAndTemp)
{
    String a("abc");
    String r = a + String("ABC");
    BOOST_REQUIRE(r[0] == a[0]);
    output << r;
    CHECK_OUTPUT("abcABC");
}

BOOST_AUTO_TEST_CASE(addingTempAndTemp)
{
    boost::test_tools::output_test_stream output;
    output << (String("abc") + String("ABC"));
    CHECK_OUTPUT("abcABC");
}

// vim: fen

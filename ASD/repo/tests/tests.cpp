#define BOOST_TEST_MODULE Tests

#ifdef BOOST_TEST_DYN_LINK
#    include <boost/test/unit_test.hpp>
#else
#    include <boost/test/included/unit_test.hpp>
#endif

#include <boost/test/tools/output_test_stream.hpp>

boost::test_tools::output_test_stream output;

#define CHECK_OUTPUT(msg) BOOST_CHECK(output.is_equal(msg))

class coutRedirect {
    std::streambuf* old;
  public:
    coutRedirect(std::streambuf* buf) : old(std::cout.rdbuf(buf)) {}
    ~coutRedirect() { std::cout.rdbuf(old); }
};

#include "Array.hpp"
#include "AVL.hpp"
#include "util.hpp"

BOOST_AUTO_TEST_SUITE(InsertionSort)

BOOST_AUTO_TEST_CASE(test1)
{
    Array<int, 5> x = { 4, 2, 4, 5, 1 };
    x.sort("insertion");
    output << x;
    CHECK_OUTPUT("1 2 4 4 5");
}

BOOST_AUTO_TEST_CASE(test2)
{
    Array<int, 100> a(2, 99);
    a.sort("insertion");
    for (std::size_t i = 0; i < a.size-1; ++i) {
        BOOST_CHECK_LE(a[i], a[i+1]);
    }
}

BOOST_AUTO_TEST_CASE(test3)
{
    Array<double, 10> x{ 10.2, 8.7, 8.3, 7.1, 6.9, 5.1, 4.3, 3.9, 2, 1.111 };
    x.sort("insertion");
    BOOST_CHECK_EQUAL(x[0], 1.111);
    BOOST_CHECK_EQUAL(x[1], 2);
    BOOST_CHECK_EQUAL(x[2], 3.9);
    BOOST_CHECK_EQUAL(x[3], 4.3);
    BOOST_CHECK_EQUAL(x[4], 5.1);
    BOOST_CHECK_EQUAL(x[5], 6.9);
    BOOST_CHECK_EQUAL(x[6], 7.1);
    BOOST_CHECK_EQUAL(x[7], 8.3);
    BOOST_CHECK_EQUAL(x[8], 8.7);
    BOOST_CHECK_EQUAL(x[9], 10.2);
}

BOOST_AUTO_TEST_CASE(test4)
{
    Array<int, 100> a(2, 99);
    a.sort("insertion");
    BOOST_CHECK(isSorted(a));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MergeSort)

BOOST_AUTO_TEST_CASE(test1)
{
    Array<int, 5> x = { 4, 2, 4, 5, 1 };
    x.sort("merge");
    output << x;
    CHECK_OUTPUT("1 2 4 4 5");
}

BOOST_AUTO_TEST_CASE(test2)
{
    Array<int, 100> a(2, 99);
    a.sort("merge");
    for (std::size_t i = 0; i < a.size-1; ++i) {
        BOOST_CHECK_LE(a[i], a[i+1]);
    }
}

BOOST_AUTO_TEST_CASE(test3)
{
    Array<double, 10> x{ 10.2, 8.7, 8.3, 7.1, 6.9, 5.1, 4.3, 3.9, 2, 1.111 };
    x.sort("merge");
    BOOST_CHECK_EQUAL(x[0], 1.111);
    BOOST_CHECK_EQUAL(x[1], 2);
    BOOST_CHECK_EQUAL(x[2], 3.9);
    BOOST_CHECK_EQUAL(x[3], 4.3);
    BOOST_CHECK_EQUAL(x[4], 5.1);
    BOOST_CHECK_EQUAL(x[5], 6.9);
    BOOST_CHECK_EQUAL(x[6], 7.1);
    BOOST_CHECK_EQUAL(x[7], 8.3);
    BOOST_CHECK_EQUAL(x[8], 8.7);
    BOOST_CHECK_EQUAL(x[9], 10.2);
}

BOOST_AUTO_TEST_CASE(test4)
{
    Array<int, 100> a(2, 99);
    a.sort("merge");
    BOOST_CHECK(isSorted(a));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(HeapSort)

BOOST_AUTO_TEST_CASE(test1)
{
    Array<int, 5> x = { 4, 2, 4, 5, 1 };
    x.sort("heap");
    output << x;
    CHECK_OUTPUT("1 2 4 4 5");
}

BOOST_AUTO_TEST_CASE(test2)
{
    Array<int, 100> a(2, 99);
    a.sort("heap");
    for (std::size_t i = 0; i < a.size-1; ++i) {
        BOOST_CHECK_LE(a[i], a[i+1]);
    }
}

BOOST_AUTO_TEST_CASE(test3)
{
    Array<double, 10> x{ 10.2, 8.7, 8.3, 7.1, 6.9, 5.1, 4.3, 3.9, 2, 1.111 };
    x.sort("heap");
    BOOST_CHECK_EQUAL(x[0], 1.111);
    BOOST_CHECK_EQUAL(x[1], 2);
    BOOST_CHECK_EQUAL(x[2], 3.9);
    BOOST_CHECK_EQUAL(x[3], 4.3);
    BOOST_CHECK_EQUAL(x[4], 5.1);
    BOOST_CHECK_EQUAL(x[5], 6.9);
    BOOST_CHECK_EQUAL(x[6], 7.1);
    BOOST_CHECK_EQUAL(x[7], 8.3);
    BOOST_CHECK_EQUAL(x[8], 8.7);
    BOOST_CHECK_EQUAL(x[9], 10.2);
}

BOOST_AUTO_TEST_CASE(test4)
{
    Array<int, 100> a(2, 99);
    a.sort("heap");
    BOOST_CHECK(isSorted(a));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AVL_tree)

BOOST_AUTO_TEST_CASE(test1)
{
    coutRedirect guard(output.rdbuf());
    AVL<int> x;
    x.insert(10);
    x.insert(20);
    x.insert(30);
    x.insert(40);
    x.insert(50);
    x.insert(25);
    x.print("pre");
    CHECK_OUTPUT("30 20 10 25 40 50 \n");
}

BOOST_AUTO_TEST_CASE(test2)
{
    coutRedirect guard(output.rdbuf());
    AVL<int> x;
    x.insert(9);
    x.insert(5);
    x.insert(10);
    x.insert(0);
    x.insert(6);
    x.insert(11);
    x.insert(-1);
    x.insert(1);
    x.insert(2);
    x.print("pre");
    CHECK_OUTPUT("9 1 0 -1 5 2 6 10 11 \n");
}

BOOST_AUTO_TEST_SUITE_END()

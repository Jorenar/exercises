#pragma once

#ifdef BOOST_TEST_DYN_LINK
    #include <boost/test/unit_test.hpp>
#else
    #include <boost/test/included/unit_test.hpp>
#endif

#include <boost/mpl/list.hpp>
#include <boost/test/tools/output_test_stream.hpp>

#include <complex>
#include <functional>
#include <initializer_list>

template<typename, size_t, size_t> class Matrix;

boost::test_tools::output_test_stream output;
std::initializer_list<std::initializer_list<int>> initList3x3{{ 1,2,3 }, { 4,5,6 }, { 7,8,9 }};
typedef boost::mpl::list<short,int,long,double,std::complex<double>> test_types;

using M1 = Matrix<int,1,1>;
using M3 = Matrix<int,3,3>;

class coutRedirect {
    std::streambuf* old;
  public:
    coutRedirect(std::streambuf* buf) : old(std::cout.rdbuf(buf)) {}
    ~coutRedirect() { std::cout.rdbuf(old); }
};

#define CHECK_OUTPUT(msg) BOOST_CHECK(output.is_equal(msg))

template<typename T, size_t N, size_t M>
void TestConstructor(std::string msg)
{
    coutRedirect guard(output.rdbuf());
    Matrix<T,N,M> foo;
    CHECK_OUTPUT(msg + "\n");
    BOOST_CHECK_EQUAL(foo.numberOfRows(), N);
    BOOST_CHECK_EQUAL(foo.numberOfColumns(), M);
}

template<typename T, size_t N, size_t M>
void TestConstructorDyn(std::string msg)
{
    coutRedirect guard(output.rdbuf());
    Matrix<T,0,0> foo(N,M);
    CHECK_OUTPUT(msg + "\n");
    BOOST_CHECK_EQUAL(foo.numberOfRows(), N);
    BOOST_CHECK_EQUAL(foo.numberOfColumns(), M);
}

template<typename T, size_t N, size_t M>
struct TestBracket {
    Matrix<T,N,M> m;
    TestBracket()
    {
        BOOST_REQUIRE(m.numberOfRows() == N);
        BOOST_REQUIRE(m.numberOfColumns() == M);
        for (size_t i = 1; i <= N; ++i) {
            for (size_t j = 1; j <= M; ++j) {
                BOOST_CHECK_EQUAL(m(i,j), T{0});
            }
        }
    }
};

// vim: fen

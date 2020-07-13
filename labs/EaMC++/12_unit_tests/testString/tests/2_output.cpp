#define BOOST_TEST_MODULE Output
#include "init_testing.hpp"

BOOST_AUTO_TEST_CASE(test0)
{
    const char* foo = "123455678900qqwerrttyyuioopasdffghjkklzxcvvbnmm1qaz2wsx3edc4rfv5tgb6yhn7ujm8ik";
    String a(foo);
    output << a;
    CHECK_OUTPUT(foo);
}

// vim: fen

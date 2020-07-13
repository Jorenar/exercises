#pragma once

#ifdef BOOST_TEST_DYN_LINK
    #include <boost/test/unit_test.hpp>
#else
    #include <boost/test/included/unit_test.hpp>
#endif

#include <boost/test/tools/output_test_stream.hpp>

#include "String.hpp"

boost::test_tools::output_test_stream output;

#define CHECK_OUTPUT(msg) BOOST_CHECK(output.is_equal(msg))

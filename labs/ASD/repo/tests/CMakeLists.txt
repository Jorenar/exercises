add_definitions(-DBOOST_TEST_DYN_LINK)
include(BoostTestHelper)

add_boost_test_file(tests.cpp util)

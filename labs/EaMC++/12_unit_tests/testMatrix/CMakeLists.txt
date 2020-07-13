cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules")

project(MatrixTests)

set(CMAKE_CXX_STANDARD 14)

#add_library(String OBJECT src/String.cpp)
include_directories(include/)

# TESTING --------------------
add_definitions(-DBOOST_TEST_DYN_LINK)
include(BoostTestHelper)
add_boost_tests_dir(tests/static)
add_boost_tests_dir(tests/dynamic)
add_boost_tests_dir(tests/mixed)

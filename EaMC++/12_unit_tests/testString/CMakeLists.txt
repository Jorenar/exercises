cmake_minimum_required(VERSION 3.10)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules")
project(StringTests)
set(CMAKE_CXX_STANDARD 14)
include_directories(src/)
add_library(String OBJECT src/String.cpp)

# TESTING
include(BoostTestHelper)
add_boost_tests_dir(tests String)

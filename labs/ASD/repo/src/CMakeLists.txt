add_library(util OBJECT util.cpp)

add_executable("${CMAKE_PROJECT_NAME}" main.cpp util)

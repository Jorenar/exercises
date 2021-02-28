cmake_minimum_required(VERSION 3.16)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(foo
  VERSION 0.0.1
  LANGUAGES CXX)

set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/static)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/dynamic)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
  "${CMAKE_BINARY_DIR}/compile_commands.json"
  "${CMAKE_SOURCE_DIR}/compile_commands.json")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g -Wall -Wextra -Wpedantic -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

include(ExternalProject)

set(DEPS_DIR ${CMAKE_BINARY_DIR}/extern) # where to install dependencies

ExternalProject_Add(bprinter
  PREFIX ""
  GIT_REPOSITORY "https://github.com/dattanchu/bprinter.git"
  GIT_SUBMODULES_RECURSE YES
  GIT_SHALLOW YES
  INSTALL_DIR "${DEPS_DIR}"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  )

add_library(BPRINTER STATIC IMPORTED)
set_target_properties(BPRINTER PROPERTIES IMPORTED_LOCATION ${DEPS_DIR}/lib/libbprinter.a)

include_directories("${DEPS_DIR}/include")
include_directories(include/)
add_subdirectory(src/)

#add_subdirectory(docs/)

cmake_minimum_required(VERSION 3.10)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(asd
  VERSION 0.0.1
  LANGUAGES CXX)

string(TOLOWER "${CMAKE_PROJECT_NAME}" EXECUTABLE_NAME)

add_definitions(-DPROJECT_NAME="${CMAKE_PROJECT_NAME}")
add_definitions(-DVERSION="${CMAKE_PROJECT_VERSION}")
add_definitions(-DEXECUTABLE_NAME="${EXECUTABLE_NAME}")

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(
    FATAL_ERROR
      "In-source builds not allowed.\n"
      "Please make a new directory and run CMake from there.\n"
      "You may need to remove CMakeCache.txt and CMakeFiles/")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/static)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/dynamic)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/compile_commands.json")
  file(RELATIVE_PATH buildRelPath "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}")

  execute_process(
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink
      "${buildRelPath}/compile_commands.json"
      "${CMAKE_SOURCE_DIR}/compile_commands.json")
endif()

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -pedantic")

include_directories(include/)

add_subdirectory(src/)

if(NOT EXECUTABLE_NAME)
  set(EXECUTABLE_NAME "${CMAKE_PROJECT_NAME}")
endif()

set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES
  OUTPUT_NAME "${EXECUTABLE_NAME}")

if(RUN_ARGS)
  add_custom_target(run
    COMMAND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME}" ${RUN_ARGS}
    DEPENDS "${CMAKE_PROJECT_NAME}"
    )
else()
  add_custom_target(run
    COMMAND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE_NAME}"
    DEPENDS "${CMAKE_PROJECT_NAME}"
    )
endif()

include(CTest)
add_subdirectory(tests/)

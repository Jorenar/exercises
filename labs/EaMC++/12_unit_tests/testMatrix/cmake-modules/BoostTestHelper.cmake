# Author:  Jorengarenar
# License: MIT

# Init
include(CTest)
find_package(
  Boost
  COMPONENTS unit_test_framework
  REQUIRED)

# Directory with tests' executables
if(NOT BIN_DIR)
  set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
endif()

function(add_boost_test testExe testName testBinDir)
  add_test(
    NAME "${testExe}:${testName}"
    COMMAND ${testExe} -t ${testName} --catch_system_error=yes
    WORKING_DIRECTORY ${testBinDir})
endfunction()

function(check_boost_test line suites testFullName)
  string(REGEX
    REPLACE ".*BOOST[_A-Z]+_TEST_CASE[_A-Z]*\\( *([A-Za-z_0-9]+).*\\).*"
    "\\1" testName "${line}")

  if("${line}" MATCHES "BOOST_[A-Z]+_TEST_CASE_TEMPLATE")
    set(testName "${testName}*")
  endif()

  if(suites)
    list(GET suites -1 suite)
  endif()

  set(${testFullName}
    "${suite}${testName}"
    PARENT_SCOPE)

  add_boost_test("${testExe}" "${suite}${testName}" "${testsBinDir}")
endfunction()

# Add Boost test source file
#     add_boost_test_file(<src> [ <libs> ... ])
function(add_boost_test_file sourceFile)
  message(${ARGV})
  get_filename_component(testExe ${sourceFile} NAME_WE)
  get_filename_component(testDir ${sourceFile} DIRECTORY)
  set(testBinDir ${BIN_DIR}/${testDir})

  add_executable(${testExe} ${sourceFile})
  set_target_properties(${testExe} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    ${testBinDir})
  target_link_libraries(${testExe} ${ARGN} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

  file(READ "${sourceFile}" srcContents)
  string(REGEX REPLACE ";" "\\\\;" srcContents "${srcContents}")
  string(REGEX REPLACE "\n" ";" srcContents "${srcContents}")

  set(suites "")
  set(testNames)
  set(multiLineComment 0)
  set(preProcIf 0)
  foreach(line ${srcContents})
    set(comment 0)

    if("${line}" MATCHES "/\\*")
      set(multiLineComment 1)
    endif()
    if("${line}" MATCHES "\\*/")
      set(multiLineComment 0)
    endif()

    if("${line}" MATCHES "//.*" OR ${multiLineComment})
      set(comment 1)
    endif()

    if(NOT ${comment})
      if("${line}" MATCHES "#if.*def")
        math(EXPR preProcIf "${preProcIf}+1")
      endif()
      if("${line}" MATCHES "#endif")
        math(EXPR preProcIf "${preProcIf}-1")
      endif()
    endif()

    if(NOT (${comment} OR ${preProcIf}))
      if("${line}" MATCHES "BOOST_AUTO_TEST_SUITE_END")
        list(POP_BACK suites)
      elseif("${line}" MATCHES "BOOST_[A-Z]+_TEST_SUITE")
        string(REGEX
          REPLACE ".*BOOST_[A-Z]+_TEST_SUITE\\( *([A-Za-z_0-9]+).*\\).*"
          "\\1" suiteName "${line}")
        if(suites)
          list(GET suites -1 prev)
        endif()
        list(APPEND suites "${prev}${suiteName}/")
      elseif("${line}" MATCHES "BOOST_[A-Z]+_TEST_CASE")
        check_boost_test("${line}" "${suites}" testFullName)
        list(APPEND testNames "${testFullName}")
      elseif("${line}" MATCHES "BOOST_TEST_CASE")
        set(atypicalTest 1)
      endif()
    elseif(
        NOT ${comment}
        AND ${preProcIf}
        AND "${line}" MATCHES "BOOST[_A-Z]*_TEST_CASE")
      set(atypicalTest 1)
    endif()
  endforeach()

  if(${atypicalTest})
    if(testNames)
      string(REPLACE ";" "," testNames "${testNames}")
      set(testsAlreadyRun \!${testNames})
    endif()

    add_test(
      NAME "${testExe}~"
      COMMAND ${testExe} -t "${testsAlreadyRun}" --catch_system_error=yes
      WORKING_DIRECTORY ${testBinDir})

    set_tests_properties("${testExe}~" PROPERTIES
      SKIP_REGULAR_EXPRESSION
      "no test cases matching filter or all test cases were disabled")
  endif()
endfunction()

# Add all tests form given directory
#     add_boost_tests_dir(<dir> [ <libs> ... ])
function(add_boost_tests_dir dir)
  file(
    GLOB testsSrcs
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${dir}/*.cpp)
  foreach(test ${testsSrcs})
    add_boost_test_file("${test}" ${ARGN})
  endforeach()
endfunction()

# vim: fen

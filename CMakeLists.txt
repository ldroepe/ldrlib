cmake_minimum_required(VERSION 3.14)
project(ldrlib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

#set(gtest_force_shared_crt 
FetchContent_MakeAvailable(googletest)

enable_testing()

set(SET_HEADERS include/sets/sets.h)
set(SET_TEST_SOURCES test/sets/sets_base.cpp)

add_executable(
    sets_test
    ${SET_HEADERS}
    ${SET_TEST_SOURCES}
)

target_include_directories(sets_test PRIVATE include/sets/)

target_link_libraries(
    sets_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(sets_test)

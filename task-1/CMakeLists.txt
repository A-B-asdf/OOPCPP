
cmake_minimum_required(VERSION 3.20)

project(BigInt)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Build googletest
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
    "googletest"
)

# main target
add_executable(
    BigInt 
    src/main.cpp 
    src/BigInt.cpp
)

# Test target
add_executable(
    test_bigint
    test/test_bigint.cpp
)

# Add src to the include directories for the test target
target_include_directories(
    test_bigint PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link test target against gtest libraries
target_link_libraries(
    test_bigint PRIVATE
    gtest gtest_main
)

target_compile_options(
    BigInt PRIVATE
    -Wall -Wextra -pedantic 
)

target_compile_options(
    test_bigint PRIVATE
    -Wall -Wextra -pedantic 
)

cmake_minimum_required(VERSION 3.10)
project(EigenNumpyBenchmark)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories for Eigen and our own headers
include_directories(
    ${PROJECT_SOURCE_DIR}/external/eigen
    ${PROJECT_SOURCE_DIR}/include
)

# Create an executable for testing the 'append' functionality
add_executable(test_append
    tests/cpp_tests/test_append.cpp
    src/append.cpp
)
cmake_minimum_required(VERSION 3.10)
project(EigenNumpyBenchmark)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories for Eigen and our own headers
include_directories(
    ${PROJECT_SOURCE_DIR}/external/eigen
    ${PROJECT_SOURCE_DIR}/external/eigen/unsupported
    ${PROJECT_SOURCE_DIR}/include
)

# Create an executable for testing the 'append' functionality
add_executable(test_append
    tests/cpp_tests/test_append.cpp
    src/append.cpp
)

# Create an executable for testing the 'matmult' functionality
add_executable(test_matmult
    tests/cpp_tests/test_matmult.cpp
    src/matmult.cpp
)

# Create an executable for testing the 'concat' functionality
add_executable(test_concat
    tests/cpp_tests/test_concat.cpp
    src/concat.cpp
)

# Create an executable for test_inner
add_executable(test_inner
    tests/cpp_tests/test_inner.cpp
    src/inner.cpp
)

# Create an executable for test_outer
add_executable(test_outer
    tests/cpp_tests/test_outer.cpp
    src/outer.cpp
)

# Create an executable for test_rot90
add_executable(test_rot90
    tests/cpp_tests/test_rot90.cpp
    src/rot90.cpp
)

# Create an executable for testing ND append (append_nd)
add_executable(test_append_nd
    tests/cpp_tests/test_append_nd.cpp
)

# Create an executable for testing ND concat (concat_nd)
add_executable(test_concat_nd
    tests/cpp_tests/test_concat_nd.cpp
)

# Create an executable for testing ND stack (stack_nd)
add_executable(test_stack_nd
    tests/cpp_tests/test_stack_nd.cpp
)

add_executable(test_fft
    tests/cpp_tests/test_fft.cpp
    src/fft.cpp
)

# Create an executable for the C++ benchmark program
add_executable(benchmark_eigen
    tests/cpp_tests/benchmark_eigen.cpp
    src/append.cpp
    src/concat.cpp
    src/inner.cpp
    src/matmult.cpp
    src/outer.cpp
    src/rot90.cpp
)
# Add optimization flags
target_compile_options(benchmark_eigen PRIVATE -O3 -march=native)
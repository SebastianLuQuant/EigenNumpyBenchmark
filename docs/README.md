# EigenNumpyBenchmark

## Overview
EigenNumpyBenchmark is a C++ project that provides NumPy-like operations (e.g., `append`, `matmult`, and more) using [Eigen](https://eigen.tuxfamily.org/) as the backend. The main goal is to compare performance between native C++/Eigen implementations and NumPy, ensuring we have a fair, consistent API for benchmarking.

## Features
- **2D Append Function**: Allows row-wise and column-wise concatenation of two matrices, with dimension checks that throw exceptions on mismatch.  
- **2D Concat Function**: Similar to `numpy.concatenate`, allows multiple matrices to be merged along a chosen axis.
- **2D matmult Function**: A straightforward matrix multiplication that mimics `numpy.matmult`, throwing exceptions on dimension mismatch.  
- (Planned) **Additional Operations**: `rot90`, `inner`, `outer`, etc.  
- (Planned) **N-Dimensional Extensions**: Utilizing Eigen's Tensor module or custom templates to handle >2D arrays.  
- (Planned) **Python Bindings**: Using tools like `pybind11` to benchmark against NumPy directly in Python.


## Installation & Dependencies
- **Eigen**: A header-only library for linear algebra. Clone or place it under `external/eigen`.  
- **C++17**: The project requires a C++17-compatible compiler (e.g., GCC 7+, Clang 6+, MSVC 2017+).  
- **CMake**: Recommended build system (version 3.10 or newer).

### Steps to Build
1. Clone this repository.
2. In the `external` folder, clone Eigen:
   ```bash
   cd external
   git clone https://gitlab.com/libeigen/eigen.git
   cd ..

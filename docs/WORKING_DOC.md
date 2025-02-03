# WORKING DOCUMENTATION

## Project Overview

MyPyEigen is a Python extension module designed to provide a NumPy-like interface while leveraging the high-performance Eigen C++ library for linear algebra operations. Our goal has been to enable fair performance comparisons between Eigen-based implementations and NumPy’s optimized routines. Over several versions, we have progressively extended the functionality from basic 2D operations to n-dimensional (ND) operations and added a bonus FFT wrapper.

## Version History and Implementation Story

### v0.1 – Initial 2D Interfaces
- **Implementation:**  
  Implemented basic 2D operations including `append`, `concat`, `matmult`, `inner`, `outer`, and `rot90` in the `include/` and `src/` directories.
- **Testing:**  
  Developed dedicated C++ tests and Python binding tests to verify correctness.
- **Outcome:**  
  Established a working baseline for our Eigen-based operations with an interface similar to NumPy.

### v0.2 – Compiler Optimization and 2D Performance Analysis
- **Enhancements:**  
  Applied compiler optimizations (`-O3`, `-march=native`) to reduce overhead.
- **Benchmarking:**  
  Compared performance between NumPy, MyPyEigen (via Python bindings), and native C++ Eigen.  
  Noted that MyPyEigen sometimes showed higher overhead, possibly due to conversion costs (e.g., converting NumPy arrays to `Eigen::MatrixXd`).
- **Outcome:**  
  Direct C++ benchmarks confirmed that data conversion contributes noticeably to the overall runtime, providing a rationale for further optimizations.

### v0.3 – ND Interfaces with Template Implementation
- **Implementation:**  
  Developed ND versions of key operations:
  - **append_nd:** Appends two 3D arrays along a specified axis.
  - **concat_nd:** Concatenates a list of 3D arrays along a specified axis.
  - **stack_nd:** Stacks a list of 2D arrays along a new axis (resulting in a 3D array) by internally converting each 2D array to an Eigen tensor and then concatenating them (using `concat_nd`).
- **Testing:**  
  Created dedicated C++ tests (`test_append_nd.cpp`, `test_concat_nd.cpp`, `test_stack_nd.cpp`) and updated Python Jupyter Notebook benchmarks.
- **Outcome:**  
  ND interfaces function correctly and mimic NumPy’s behavior, though they reveal additional overhead due to conversion and copying.

### v0.4 – Bonus FFT Wrapper
- **Implementation:**  
  Developed an FFT wrapper (declared in `fft.h` and implemented in `fft.cpp`) using Eigen’s FFT module.  
  The Python binding (`pe.fft`) converts a 1D NumPy array to a `std::vector<double>`, calls the FFT function, and returns a 1D NumPy array of complex numbers.
- **Testing:**  
  Verified FFT functionality with dedicated C++ tests (`test_fft.cpp`) and Python benchmark notebooks.
- **Outcome:**  
  The FFT wrapper shows competitive performance, especially for smaller input sizes, compared to NumPy’s FFT.

## Testing and Benchmarking

### C++ Testing
- C++ tests are located in `tests/cpp_tests/`:
  - 2D tests: `test_append.cpp`, `test_concat.cpp`, `test_matmult.cpp`, `test_inner.cpp`, `test_outer.cpp`, `test_rot90.cpp`
  - ND tests: `test_append_nd.cpp`, `test_concat_nd.cpp`, `test_stack_nd.cpp`
  - FFT test: `test_fft.cpp`
- Benchmarks (e.g., `benchmark_eigen.cpp`) measure pure computational performance (excluding Python binding overhead) using high optimization flags.

### Python Testing and Benchmarking
- Jupyter Notebooks under `tests/py_tests/` (e.g., `benchmark_0.1.ipynb`, `benchmark_0.3_nd.ipynb`, `benchmark_0.4_fft.ipynb`) are used to run functional tests and performance benchmarks.
- Benchmarks use a fixed random seed, preheating, and averaging over multiple iterations to ensure reliability.

## Performance Benchmark Analysis

The following benchmark results compare the performance of key operations in NumPy, MyPyEigen (via Python bindings), and native C++ Eigen implementations. Our benchmarks were designed with the following considerations:

1. **Preheating/Caching:**  
   We preheat function calls to minimize one-time initialization or cache-warmup overhead.

2. **Reproducibility:**  
   A fixed random seed (`np.random.seed(12345)`) is used to ensure that test cases are consistent across runs.

3. **Data Preprocessing Exclusion:**  
   Test arrays are generated before timing so that the overhead of data creation and conversion is excluded from the benchmark.

4. **Range of Test Sizes:**  
   Benchmarks cover a wide range of sizes (from 10x10 to 5000x5000) to observe how performance scales with problem size.

5. **Data Type Consistency:**  
   All arrays are generated with `np.float64` (64-bit double) to ensure a fair comparison with Eigen's double-based computations.

**Key Takeaways:**
- **Matrix Multiplication (`matmult`):**  
  NumPy’s multi-threaded BLAS routines give it a significant advantage for large matrices. Our Eigen-based implementations are 4–5× slower at larger scales.
- **Row-wise Appending and Concatenation:**  
  While differences are small for small matrices, the overhead becomes significant for larger matrices—likely due to additional data conversion and memory copy operations.
- **Vector Operations (`inner` and `outer`):**  
  Native C++ Eigen is exceptionally fast for small vectors (up to 23× speedup), though MyPyEigen’s binding overhead makes it 2–4× slower than NumPy.
- **Matrix Rotation (`rot90`):**  
  NumPy’s zero-copy, view-based rotation is orders of magnitude faster than our Eigen-based implementation, which performs physical data rearrangement.
- **FFT:**  
  Our FFT wrapper outperforms NumPy’s FFT for small input sizes (up to 2.67× faster) and remains competitive for larger sizes, indicating that for certain operations Eigen’s FFT is very efficient.

Overall, while MyPyEigen provides a convenient and consistent interface with Eigen, it suffers from moderate overhead due to data conversion and binding. NumPy remains superior for large-scale operations, but native C++ Eigen shows strong performance in micro-benchmarks for vector operations.

## Future Work

- **Optimize Data Conversion:**  
  Implement a `to_eigen` preprocessing step to minimize repeated conversions.
- **Extend ND Interfaces:**  
  Add further ND operations (advanced slicing, higher-dimensional stacking, etc.) and optimize their performance.
- **Dynamic Template Instantiation:**  
  Investigate dynamic instantiation of templates based on input dimensions, while monitoring for any additional overhead.
- **Enhance FFT Wrapper:**  
  Expand FFT functionality to include normalization, inverse FFT, and additional parameters.
- **Comprehensive Performance Reporting:**  
  Prepare detailed performance reports with graphical analyses comparing Eigen-based operations and NumPy’s routines.

## Conclusion

MyPyEigen demonstrates that a NumPy-like interface can be built using Eigen to deliver high-performance linear algebra operations. Although additional overhead exists due to data conversion and Python binding, especially in ND operations, our project lays a solid foundation for further optimization and extension.


# MyPyEigen

MyPyEigen is a Python extension module that provides high-performance linear algebra operations using the Eigen C++ library. The module is designed with an interface similar to NumPy, enabling a fair “apple-to-apple” performance comparison between Eigen and NumPy for common linear algebra tasks. The project implements both 2D and n-dimensional (ND) operations and includes a bonus FFT wrapper.

## Features

### 2D Operations
- **append**: Append two 2D matrices along a specified axis (mimics NumPy’s append/vstack/hstack).
- **concat**: Concatenate multiple 2D matrices along a specified axis (similar to NumPy’s concatenate).
- **matmult**: Perform matrix multiplication (equivalent to NumPy’s matmul or the `@` operator).
- **inner**: Compute the inner product of 1D vectors.
- **outer**: Compute the outer product of 1D vectors.
- **rot90**: Rotate a 2D matrix by multiples of 90°.

### ND Operations
- **append_nd**:  
  Appends two 3D arrays along a specified axis.  
  (Implemented in `include/append_nd.h` and `append_nd_impl.hpp`)
- **concat_nd**:  
  Concatenates a list of 3D arrays along a specified axis.  
  (Implemented in `include/concat_nd.h` and `concat_nd_impl.hpp`)
- **stack_nd**:  
  Stacks a list of 2D arrays along a new axis, resulting in a 3D array.  
  (Implemented in `include/stack_nd.h` and `stack_nd_impl.hpp`)

### Bonus FFT Wrapper
- **fft**:  
  Computes the 1D discrete Fourier Transform using Eigen's FFT module.  
  - Accepts a 1D NumPy array (`np.float64`) and returns a 1D NumPy array of complex numbers.  
  - The interface is similar to `numpy.fft.fft` (supporting basic functionality).

## Repository Structure
   ```
   EigenNumpyBenchmark/
   ├── bindings/                # Python binding code (with pyproject.toml)
   ├── build/                   # Build output directory
   ├── CMakeLists.txt           # Top-level CMake build configuration
   ├── docs/                    # Documentation (README.md, WORKING_DOC.md)
   ├── external/                # Third-party libraries (e.g., Eigen)
   ├── include/                 # Header files
   │   ├── append.h
   │   ├── concat.h
   │   ├── inner.h
   │   ├── matmult.h
   │   ├── outer.h
   │   ├── rot90.h
   │   ├── append_nd.h
   │   ├── append_nd_impl.hpp
   │   ├── concat_nd.h
   │   ├── concat_nd_impl.hpp
   │   ├── stack_nd.h
   │   ├── stack_nd_impl.hpp
   │   └── fft.h
   ├── src/                     # Source files
   │   ├── append.cpp
   │   ├── concat.cpp
   │   ├── inner.cpp
   │   ├── matmult.cpp
   │   ├── outer.cpp
   │   ├── rot90.cpp
   │   └── fft.cpp
   ├── tests/                   # Test and benchmark code
   │   ├── cpp_tests/           # C++ tests and benchmarks:
   │   │   ├── benchmark_eigen.cpp
   │   │   ├── test_append.cpp
   │   │   ├── test_concat.cpp
   │   │   ├── test_inner.cpp
   │   │   ├── test_matmult.cpp
   │   │   ├── test_outer.cpp
   │   │   ├── test_rot90.cpp
   │   │   ├── test_append_nd.cpp
   │   │   ├── test_concat_nd.cpp
   │   │   └── test_stack_nd.cpp
   │   └── py_tests/            # Python tests and benchmarks (Jupyter Notebooks):
   │         benchmark_0.1.ipynb
   │         benchmark_0.2.ipynb
   │         benchmark_0.3_nd.ipynb
   │         benchmark_0.4_fft.ipynb
   └── venv/                    # Python virtual environment
   ```

## Building and Testing

### C++ Tests and Benchmarks
1. Navigate to the top-level directory and create a build folder:
   ```bash
   mkdir build && cd build
   cmake ..
   make -j
   ```

The test executables (e.g., test_append_nd, test_concat_nd, test_stack_nd, test_fft, etc.) are generated in the build directory. Run them individually to verify functionality and performance.
### Python Binding
Go to the bindings/ directory:
```bash
cd bindings
```
Build the extension:
```bash
python3 setup.py build
```
Install it:
```bash
pip install .
```
Import the module in Python:
```python
import MyPyEigen as pe
```
### Benchmarking (Python)
Jupyter Notebooks under tests/py_tests/ are provided for benchmarking and comparing MyPyEigen functions with NumPy’s native implementations.

## Version History
- v0.1: Initial implementation of 2D interfaces (append, concat, matmult, inner, outer, rot90).
- v0.2: optimized with O3
- v0.3: Added ND interfaces (append_nd, concat_nd, stack_nd).
- v0.4: Added bonus FFT wrapper.


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

### Matrix Multiplication (`matmult`)
| Size       | NumPy (sec)   | MyPyEigen (sec) | C++ Eigen (sec) | Eigen/Numpy Speedup | MyPyEigen/Numpy Speedup |
|------------|---------------|-----------------|-----------------|---------------------|-------------------------|
| 10x10      | 0.000001504   | 0.000002096     | 0.000005192     | 0.29x (Slower)      | 0.72x (Slower)          |
| 50x50      | 0.000004983   | 0.000012567     | 0.00002195      | 0.23x (Slower)      | 0.40x (Slower)          |
| 100x100    | 0.000013821   | 0.000065992     | 0.000149117     | 0.09x (Slower)      | 0.21x (Slower)          |
| 500x500    | 0.000949358   | 0.006314442     | 0.00776362      | 0.12x (Slower)      | 0.15x (Slower)          |
| 1000x1000  | 0.007864650   | 0.053339788     | 0.045176       | 0.17x (Slower)      | 0.15x (Slower)          |
| 2000x2000  | 0.063897550   | 0.382685758     | 0.376416       | 0.17x (Slower)      | 0.17x (Slower)          |
| 5000x5000  | 1.013861154   | 6.388341517     | 6.05327        | 0.17x (Slower)      | 0.16x (Slower)          |

### Row-wise Appending (`append`, axis=0)
| Size       | NumPy (sec)   | MyPyEigen (sec) | C++ Eigen (sec) | Eigen/Numpy Speedup | MyPyEigen/Numpy Speedup |
|------------|---------------|-----------------|-----------------|---------------------|-------------------------|
| 10x10      | 0.000001867   | 0.000001800     | 0.000001396     | 1.34x (Faster)      | 1.04x (Similar)         |
| 50x50      | 0.000002612   | 0.000019946     | 0.000021517     | 0.12x (Slower)      | 0.13x (Slower)          |
| 100x100    | 0.000004733   | 0.000052279     | 0.000010471     | 0.45x (Slower)      | 0.09x (Slower)          |
| 500x500    | 0.000214204   | 0.001448987     | 0.000475288     | 0.45x (Slower)      | 0.15x (Slower)          |
| 1000x1000  | 0.000541433   | 0.006866908     | 0.00139505      | 0.39x (Slower)      | 0.08x (Slower)          |
| 2000x2000  | 0.004133825   | 0.042485529     | 0.00753595      | 0.55x (Slower)      | 0.10x (Slower)          |
| 5000x5000  | 0.035949937   | 0.429655021     | 0.0594201       | 0.61x (Slower)      | 0.08x (Slower)          |

### Row-wise Concatenation (`concat`, axis=0)
| Size       | NumPy (sec)   | MyPyEigen (sec) | C++ Eigen (sec) | Eigen/Numpy Speedup | MyPyEigen/Numpy Speedup |
|------------|---------------|-----------------|-----------------|---------------------|-------------------------|
| 10x10      | 0.000000983   | 0.000002087     | 0.000000517     | 1.90x (Faster)      | 0.47x (Slower)          |
| 50x50      | 0.000001975   | 0.000010208     | 0.000012758     | 0.15x (Slower)      | 0.19x (Slower)          |
| 100x100    | 0.000004913   | 0.000046717     | 0.000015204     | 0.32x (Slower)      | 0.11x (Slower)          |
| 500x500    | 0.000366783   | 0.002584196     | 0.000613713     | 0.60x (Slower)      | 0.14x (Slower)          |
| 1000x1000  | 0.001426362   | 0.010688083     | 0.00327692      | 0.44x (Slower)      | 0.13x (Slower)          |
| 2000x2000  | 0.005924200   | 0.054426763     | 0.0120489       | 0.49x (Slower)      | 0.11x (Slower)          |
| 5000x5000  | 0.053742600   | 0.641397308     | 0.0871322       | 0.62x (Slower)      | 0.08x (Slower)          |

### Vector Dot Product (`inner`)
| Vector Size | NumPy (sec) | MyPyEigen (sec) | C++ Eigen (sec) | Eigen/Numpy Speedup | MyPyEigen/Numpy Speedup |
|-------------|-------------|-----------------|-----------------|---------------------|-------------------------|
| 10          | 0.000000445 | 0.000000959     | 0.000000019     | 23.42x (Faster)     | 0.46x (Slower)          |
| 50          | 0.000000445 | 0.000000928     | 0.000000021     | 21.19x (Faster)     | 0.48x (Slower)          |
| 100         | 0.000000454 | 0.000000957     | 0.000000023     | 19.74x (Faster)     | 0.47x (Slower)          |
| 500         | 0.000000508 | 0.000001049     | 0.000000087     | 5.84x (Faster)      | 0.48x (Slower)          |
| 1000        | 0.000000591 | 0.000001255     | 0.000000167     | 3.54x (Faster)      | 0.47x (Slower)          |
| 2000        | 0.000000737 | 0.000001615     | 0.000000331     | 2.23x (Faster)      | 0.46x (Slower)          |
| 5000        | 0.000001217 | 0.000005441     | 0.000000811     | 1.50x (Faster)      | 0.22x (Slower)          |

### Vector Outer Product (`outer`)
| Vector Size | NumPy (sec) | MyPyEigen (sec) | C++ Eigen (sec) | Eigen/Numpy Speedup | MyPyEigen/Numpy Speedup |
|-------------|-------------|-----------------|-----------------|---------------------|-------------------------|
| 10          | 0.000001307 | 0.000001396     | 0.000000082    | 15.94x (Faster)     | 0.94x (Similar)         |
| 50          | 0.000002482 | 0.000002790     | 0.000000603    | 4.12x (Faster)      | 0.89x (Slower)          |
| 100         | 0.000021144 | 0.000010798     | 0.000002074    | 10.19x (Faster)     | 1.96x (Faster)          |
| 500         | 0.000202705 | 0.000354609     | 0.000132079    | 1.53x (Faster)      | 0.57x (Slower)          |
| 1000        | 0.000821448 | 0.001621035     | 0.000506116    | 1.62x (Faster)      | 0.51x (Slower)          |
| 2000        | 0.003679805 | 0.008724991     | 0.00263865     | 1.39x (Faster)      | 0.42x (Slower)          |
| 5000        | 0.027354049 | 0.108607435     | 0.0182483      | 1.50x (Faster)      | 0.25x (Slower)          |

### Matrix 90° Rotation (`rot90`)
| Size       | NumPy (sec) | MyPyEigen (sec) | C++ Eigen (sec) | Eigen/Numpy Speedup | MyPyEigen/Numpy Speedup |
|------------|-------------|-----------------|-----------------|---------------------|-------------------------|
| 10x10      | 0.000003645 | 0.000001254     | 0.000000207    | 17.61x (Faster)     | 2.91x (Faster)          |
| 50x50      | 0.000003582 | 0.000004189     | 0.000001542    | 2.32x (Faster)      | 0.85x (Slower)          |
| 100x100    | 0.000003571 | 0.000032559     | 0.000014167    | 0.25x (Slower)      | 0.11x (Slower)          |
| 500x500    | 0.000003550 | 0.000796685     | 0.000322017    | 0.01x (Slower)      | 0.004x (Slower)         |
| 1000x1000  | 0.000003642 | 0.004533528     | 0.00184697     | 0.002x (Slower)     | 0.0008x (Slower)        |
| 2000x2000  | 0.000003627 | 0.022455351     | 0.0095618      | 0.0004x (Slower)    | 0.0002x (Slower)        |
| 5000x5000  | 0.000003612 | 0.334358389     | 0.111125       | 0.00003x (Slower)   | 0.00001x (Slower)       |

### FFT Benchmark
| Size    | NumPy (sec)   | MyPyEigen (sec) | Speedup (MyPyEigen vs NumPy) |
|---------|---------------|-----------------|------------------------------|
| 10      | 0.000004652   | 0.000001740     | **2.67x** (Faster)           |
| 50      | 0.000004967   | 0.000002290     | **2.17x** (Faster)           |
| 100     | 0.000005365   | 0.000002746     | **1.95x** (Faster)           |
| 500     | 0.000008058   | 0.000006335     | **1.27x** (Faster)           |
| 1000    | 0.000013530   | 0.000011260     | **1.20x** (Faster)           |
| 2000    | 0.000020867   | 0.000020802     | **1.00x** (Similar)          |
| 5000    | 0.000121157   | 0.000061976     | **1.95x** (Faster)           |
| 10000   | 0.000189841   | 0.000113537     | **1.67x** (Faster)           |
| 20000   | 0.000224010   | 0.000204683     | **1.09x** (Faster)           |
| 50000   | 0.000598528   | 0.000564668     | **1.06x** (Faster)           |
| 100000  | 0.001451865   | 0.001233335     | **1.18x** (Faster)           |
| 200000  | 0.003095395   | 0.002721594     | **1.14x** (Faster)           |
| 500000  | 0.007363444   | 0.007539679     | **0.98x** (Similar)          |

## Analysis

- **Matrix Multiplication (`matmult`):**  
  NumPy’s highly optimized BLAS routines provide a significant speed advantage, especially for large matrices. Our Eigen-based implementations run 4–5× slower in large-scale multiplications.

- **Row-wise Appending (`append`):**  
  For small matrices, performance is similar between NumPy and MyPyEigen; however, as matrix size increases, MyPyEigen is consistently slower, likely due to data conversion overhead and less aggressive memory optimization.

- **Row-wise Concatenation (`concat`):**  
  NumPy achieves near zero-copy efficiency while our Eigen-based concatenation, which involves explicit copying via slice operations, remains slower. The speedup factors indicate that MyPyEigen is roughly 7–12× slower.

- **Vector Operations (`inner` and `outer`):**  
  In small-scale vector dot and outer products, C++ Eigen shows significant speedups over NumPy (up to 23× in some cases), but MyPyEigen consistently suffers from the binding overhead, making it 2–4× slower than NumPy.

- **Matrix Rotation (`rot90`):**  
  NumPy’s rotation leverages zero-copy techniques (modifying metadata), making it orders of magnitude faster than our Eigen-based implementation, which performs an actual data rearrangement.

- **FFT:**  
  Our FFT wrapper in MyPyEigen is faster than NumPy’s FFT for small sizes (up to 2.67× faster) and remains competitive for larger sizes. This demonstrates that for some operations, especially those where Eigen’s FFT is well-optimized, our wrapper can outperform NumPy.

In summary, while our Eigen-based implementation exhibits some overhead (particularly in operations that require data copying or complex slicing, such as `rot90` and concatenation), it shows notable strengths in vector operations and FFT performance for certain input sizes. The benchmark results indicate that:
- NumPy remains superior for large-scale matrix operations due to its reliance on highly optimized BLAS libraries.
- C++ Eigen (when used natively) outperforms in small-scale vector operations.
- MyPyEigen, as a Python binding, incurs a moderate overhead, generally rendering it 2–10× slower than native C++ Eigen depending on the operation.

By following these benchmarks and considerations, we have a clear picture of the trade-offs between ease of use in Python versus raw performance in C++.


## Future Work
- Optimize data conversion between NumPy and Eigen to further reduce overhead. For example: use `to_eigen` to preprocessing the input data.
- Extend ND interfaces with additional operations (advanced slicing, higher-dimensional stacking, etc.). Implemented the dynamic type for ND interfaces.
- Enhance the FFT wrapper with additional features (normalization, inverse FFT).
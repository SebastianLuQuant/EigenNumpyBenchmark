# Working Doc

This file logs the tasks and changes done in each commit.

## Commit 2: Implemented 2D Append with Exception Handling

**Date**: 2025-01-30  
**Author**: Yichen Lu

### What was done
- Revisited the `append` function to align with NumPy's behavior:
  - Throws `std::invalid_argument` if the dimensions do not match.
  - Supports `axis=0` (row-wise) and `axis=1` (column-wise).
- Updated the test (`test_append.cpp`) to verify exceptions are thrown as expected.
- Updated `docs/README.md` to reflect this progress.

### Key Points
- We remain focused on **2D** for now. Future commits may add an **N-dimensional** version using `Eigen::Tensor`. And the 2d version will be renamed as `append_2d`
- The function signature in `append.h` now explicitly states the exception behavior.

### Next Actions
- Potentially implement other NumPy-like operations (e.g., `matmult`).
- Add a benchmark or main function to measure performance.
- Integrate Python bindings.

## Commit 3: Implement `matmult` for 2D multiplication

**Date**: 2025-01-31  
**Author**: Yichen Lu

### What was done
- Created `matmult.h` and `matmult.cpp` to handle 2D matrix multiplication with Eigen.
- Throws `std::invalid_argument` if `A.cols() != B.rows()`.
- Added a new test executable (`test_matmult`) to verify:
  - Correct multiplication output.
  - Proper exception handling on dimension mismatch.
- Updated `docs/README.md` to include `matmult` under features.

### Next Steps
- Potentially implement `concat`, `rot90`, or `inner`, `outer` for further NumPy-like functionalities.
- Investigate Python bindings if we want direct comparisons with NumPy in Python code.


## Commit 4: Implement 'concat' for multiple 2D matrices

**Date**: 2025-02-01
**Author**: Yichen Lu

### What was done
- Created a new API: `concat(const std::vector<Eigen::MatrixXd>&, int axis)` in `concat.h`/`concat.cpp`.
- Allows row-wise or column-wise concatenation of multiple matrices (2D only).
- Throws `std::invalid_argument` for dimension mismatch or invalid axis.
- Added `test_concat.cpp` to verify row/column concatenation and exception scenarios.
- Updated `CMakeLists.txt` to compile the new test, updated `docs/README.md` to reflect the new feature.

### Notes
- This function generalizes `append` for multiple inputs.
- Future expansions might handle N-dimensional arrays, using `Eigen::Tensor`.

### Next Steps
- Possibly add `rot90`, `inner`, or `outer`.
- Further refine or unify the APIs for all these NumPy-like functionalities.
- (Optionally) Begin Python bindings or add benchmark code.

## Commit 5: Implement 'inner' and 'outer' for vector operations

**Date**: 2025-02-02
**Author**: Yichen Lu

### What was done
- Added `inner.h`/`.cpp` for 1D dot product.
- Added `outer.h`/`.cpp` for outer product of two 1D vectors.
- Each function has its own test: `test_inner.cpp`, `test_outer.cpp`.
- Updated CMakeLists.txt to compile `test_inner` and `test_outer`.
- Updated `README.md` to reflect the new functionalities.

### Notes
- We currently handle only simple 1D vectors for `inner` and `outer`. 
- For multi-dimensional arrays, further extension is possible.
- No dimension mismatch check in `outer`, because it doesn't require matching sizes. 

### Next Steps
- Possibly implement `rot90`, or consider going into N-dimensional territory.
- Start Python binding for direct comparison with NumPy.
- Explore performance benchmarks for these operations.
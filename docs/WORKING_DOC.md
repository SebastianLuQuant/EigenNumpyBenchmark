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
- Potentially implement other NumPy-like operations (e.g., `matmul`).
- Add a benchmark or main function to measure performance.
- Integrate Python bindings.


# EigenNumpyBenchmark

## Overview
This project aims to compare the performance of Eigen and NumPy by implementing multiple C++ wrappers that mimic NumPy's functionality. The goal is to achieve a fair benchmark between the two.

## Current Status
- **Initial Commit**: Created project structure with multiple placeholders in the 'include/' directory.
- Future commits will add:
  - Eigen as a dependency (in `external/`)
  - Multiple functions such as `append`, `matmul`, `concat`, `rot90`, etc.
  - Python bindings via pybind11 or another tool
  - Comprehensive testing (both C++ and Python)
  - Detailed performance report
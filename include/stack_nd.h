#ifndef EIGEN_NUMPY_BENCHMARK_STACK_ND_H
#define EIGEN_NUMPY_BENCHMARK_STACK_ND_H

#include <unsupported/Eigen/CXX11/Tensor>
#include <stdexcept>
#include <vector>

// stack_nd: Stacks a vector of Eigen::Tensor<double, Rank> along a new axis.
// The new axis index can range from 0 to Rank (inclusive). The result is a tensor
// of rank (Rank+1). For example, for Rank=2, stacking two matrices along axis=0
// produces a tensor of shape (2, rows, cols).
template<int Rank>
Eigen::Tensor<double, Rank+1> stack_nd(const std::vector<Eigen::Tensor<double, Rank>>& tensors,
                                       int axis);

#include "stack_nd_impl.hpp"

#endif // EIGEN_NUMPY_BENCHMARK_STACK_ND_H

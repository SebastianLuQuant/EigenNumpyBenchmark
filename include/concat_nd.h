#ifndef EIGEN_NUMPY_BENCHMARK_CONCAT_ND_H
#define EIGEN_NUMPY_BENCHMARK_CONCAT_ND_H

#include <unsupported/Eigen/CXX11/Tensor>
#include <stdexcept>
#include <vector>

// concat_nd: Concatenates a vector of Eigen::Tensor<double, Rank> along a specified axis.
// Throws std::invalid_argument if the input tensor list is empty,
// if the axis is out of bounds, or if any non-concatenated dimensions do not match.
template<int Rank>
Eigen::Tensor<double, Rank> concat_nd(const std::vector<Eigen::Tensor<double, Rank>>& tensors,
                                        int axis);

#include "concat_nd_impl.hpp"  // Include template implementation

#endif // EIGEN_NUMPY_BENCHMARK_CONCAT_ND_H

#ifndef EIGEN_NUMPY_BENCHMARK_APPEND_ND_H
#define EIGEN_NUMPY_BENCHMARK_APPEND_ND_H

#include <unsupported/Eigen/CXX11/Tensor>
#include <stdexcept>
#include <vector>

// Template function for ND append.
// This function appends two Eigen::Tensor<double, Rank> objects along the specified axis.
// It throws a std::invalid_argument exception if the axis is out of bounds or if dimensions (other than the concatenation axis) do not match.
template<int Rank>
Eigen::Tensor<double, Rank> append_nd(const Eigen::Tensor<double, Rank>& a,
                                      const Eigen::Tensor<double, Rank>& b,
                                      int axis);

// Include the template implementation.
#include "append_nd_impl.hpp"

#endif // EIGEN_NUMPY_BENCHMARK_APPEND_ND_H

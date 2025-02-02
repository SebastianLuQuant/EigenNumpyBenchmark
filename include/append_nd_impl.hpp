#ifndef EIGEN_NUMPY_BENCHMARK_APPEND_ND_IMPL_HPP
#define EIGEN_NUMPY_BENCHMARK_APPEND_ND_IMPL_HPP

#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>

template<int Rank>
Eigen::Tensor<double, Rank> append_nd(const Eigen::Tensor<double, Rank>& a,
                                      const Eigen::Tensor<double, Rank>& b,
                                      int axis) {
    if (axis < 0 || axis >= Rank)
        throw std::invalid_argument("append_nd: axis is out of bounds.");
    // Check that for each axis (except the concatenation axis), dimensions match.
    for (int i = 0; i < Rank; ++i) {
        if (i == axis) continue;
        if (a.dimension(i) != b.dimension(i))
            throw std::invalid_argument("append_nd: dimension mismatch on non-concatenated axis.");
    }
    // Use Eigen's built-in concatenate method.
    auto concatOp = a.concatenate(b, axis);
    Eigen::Tensor<double, Rank> result = concatOp;
    return result;
}

#endif // EIGEN_NUMPY_BENCHMARK_APPEND_ND_IMPL_HPP

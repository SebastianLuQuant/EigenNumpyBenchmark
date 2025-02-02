#ifndef EIGEN_NUMPY_BENCHMARK_CONCAT_ND_IMPL_HPP
#define EIGEN_NUMPY_BENCHMARK_CONCAT_ND_IMPL_HPP

#include "concat_nd.h"
#include <array>

template<int Rank>
Eigen::Tensor<double, Rank> concat_nd(const std::vector<Eigen::Tensor<double, Rank>>& tensors,
                                        int axis) {
    if (tensors.empty()) {
        throw std::invalid_argument("concat_nd: tensor list is empty.");
    }
    if (axis < 0 || axis >= Rank) {
        throw std::invalid_argument("concat_nd: axis is out of bounds.");
    }
    
    // Get dimensions from the first tensor.
    auto dims = tensors[0].dimensions();
    // Calculate total size along the concatenation axis and check other axes.
    Eigen::Index total = dims[axis];
    for (size_t i = 1; i < tensors.size(); ++i) {
        auto dims_i = tensors[i].dimensions();
        for (int j = 0; j < Rank; ++j) {
            if (j == axis) continue;
            if (dims_i[j] != dims[j]) {
                throw std::invalid_argument("concat_nd: dimension mismatch on non-concatenated axis.");
            }
        }
        total += dims_i[axis];
    }
    
    // Build result dimensions: same as dims, but along 'axis' set to total.
    Eigen::array<Eigen::Index, Rank> result_dims;
    for (int i = 0; i < Rank; ++i) {
        result_dims[i] = dims[i];
    }
    result_dims[axis] = total;
    
    // Create result tensor.
    Eigen::Tensor<double, Rank> result(result_dims);
    
    // Use slice assignment to copy each tensor into the result.
    Eigen::Index offset = 0;
    for (const auto& t : tensors) {
        Eigen::array<Eigen::Index, Rank> offsets;
        Eigen::array<Eigen::Index, Rank> extents;
        for (int i = 0; i < Rank; ++i) {
            if (i == axis) {
                offsets[i] = offset;
                extents[i] = t.dimension(i);
            } else {
                offsets[i] = 0;
                extents[i] = t.dimension(i);
            }
        }
        result.slice(offsets, extents) = t;
        offset += t.dimension(axis);
    }
    
    return result;
}

#endif // EIGEN_NUMPY_BENCHMARK_CONCAT_ND_IMPL_HPP

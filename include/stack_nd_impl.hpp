#ifndef EIGEN_NUMPY_BENCHMARK_STACK_ND_IMPL_HPP
#define EIGEN_NUMPY_BENCHMARK_STACK_ND_IMPL_HPP

#include "stack_nd.h"
#include "concat_nd.h"


template<int Rank>
Eigen::Tensor<double, Rank+1> stack_nd(const std::vector<Eigen::Tensor<double, Rank>>& tensors,
                                       int axis) {
    if (tensors.empty()) {
        throw std::invalid_argument("stack_nd: tensor list is empty.");
    }
    // For stacking, valid axis is in [0, Rank] (inserting a new dimension)
    if (axis < 0 || axis > Rank) {
        throw std::invalid_argument("stack_nd: axis is out of bounds.");
    }

    // Get dimensions from the first tensor.
    auto dims = tensors[0].dimensions();
    // Check that all tensors have the same dimensions.
    for (size_t i = 1; i < tensors.size(); ++i) {
        auto dims_i = tensors[i].dimensions();
        for (int j = 0; j < Rank; ++j) {
            if (dims_i[j] != dims[j])
                throw std::invalid_argument("stack_nd: dimension mismatch among input tensors.");
        }
    }

    // For each tensor, expand its dimensions by inserting a new axis at position 'axis'.
    std::vector<Eigen::Tensor<double, Rank+1>> expanded;
    for (const auto& t : tensors) {
        // Create new dimensions: size is same as original, but insert a dimension of 1 at index 'axis'.
        Eigen::array<Eigen::Index, Rank+1> new_dims;
        for (int i = 0; i < Rank+1; ++i) {
            if (i < axis) {
                new_dims[i] = dims[i];
            } else if (i == axis) {
                new_dims[i] = 1;
            } else {
                new_dims[i] = dims[i - 1];
            }
        }
        // Reshape the tensor t to have shape new_dims.
        auto t_expanded_expr = t.reshape(new_dims);
        // Evaluate the expression into a concrete tensor.
        Eigen::Tensor<double, Rank+1> t_expanded = t_expanded_expr;
        expanded.push_back(t_expanded);
    }

    // Now use ND concat to concatenate the expanded tensors along the new axis.
    // This is effectively our ND stack.
    Eigen::Tensor<double, Rank+1> result = concat_nd<Rank+1>(expanded, axis);
    return result;
}

#endif // EIGEN_NUMPY_BENCHMARK_STACK_ND_IMPL_HPP

#ifndef EIGEN_NUMPY_BENCHMARK_CONCAT_H
#define EIGEN_NUMPY_BENCHMARK_CONCAT_H

#include <Eigen/Dense>
#include <stdexcept>
#include <vector>

/**
 * @brief Concatenate multiple 2D matrices along the specified axis.
 *
 * Similar to numpy.concatenate((A, B, ...), axis=?), but only supports 2D.
 *
 * @param matrices A list of Eigen::MatrixXd to be concatenated.
 * @param axis     0 for row-wise, 1 for column-wise.
 * @return         A new Eigen::MatrixXd containing the concatenation.
 * @throws std::invalid_argument if axis is out of range or dimension mismatch occurs.
 */
Eigen::MatrixXd concat(const std::vector<Eigen::MatrixXd>& matrices, int axis);

#endif // EIGEN_NUMPY_BENCHMARK_CONCAT_H

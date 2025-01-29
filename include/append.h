#ifndef EIGEN_NUMPY_BENCHMARK_APPEND_H
#define EIGEN_NUMPY_BENCHMARK_APPEND_H

#include <Eigen/Dense>
#include <stdexcept>

/**
 * @brief Append one matrix to another along the specified axis.
 *
 * This function mimics the behavior of numpy.append for 2D matrices.
 * It supports axis=0 for row-wise concatenation, and axis=1 for column-wise.
 * If dimensions are mismatched, the function throws an exception.
 *
 * @param base   The base matrix.
 * @param values The matrix to be appended.
 * @param axis   0 for row-wise, 1 for column-wise.
 * @return       A new Eigen::MatrixXd containing the appended result.
 * @throws std::invalid_argument if axis is out of range or dimension mismatch occurs.
 */
Eigen::MatrixXd append(const Eigen::MatrixXd& base,
                       const Eigen::MatrixXd& values,
                       int axis);

#endif // EIGEN_NUMPY_BENCHMARK_APPEND_H

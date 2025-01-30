#ifndef EIGEN_NUMPY_BENCHMARK_OUTER_H
#define EIGEN_NUMPY_BENCHMARK_OUTER_H

#include <Eigen/Dense>
#include <stdexcept>

/**
 * @brief Compute the outer product of two 1D vectors, returning a matrix.
 *
 * Mimics numpy.outer(v1, v2). The result is v1.size() x v2.size().
 *
 * @param v1 A 1D vector (Eigen::VectorXd)
 * @param v2 A 1D vector (Eigen::VectorXd)
 * @return   An Eigen::MatrixXd representing the outer product v1 * v2^T.
 */
Eigen::MatrixXd outer(const Eigen::VectorXd& v1, const Eigen::VectorXd& v2);

#endif // EIGEN_NUMPY_BENCHMARK_OUTER_H

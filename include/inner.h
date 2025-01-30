#ifndef EIGEN_NUMPY_BENCHMARK_INNER_H
#define EIGEN_NUMPY_BENCHMARK_INNER_H

#include <Eigen/Dense>
#include <stdexcept>

/**
 * @brief Compute the inner product (dot product) of two 1D vectors.
 *
 * Mimics numpy.inner for 1D vectors, returning a single double value.
 *
 * @param v1 A 1D vector (Eigen::VectorXd)
 * @param v2 A 1D vector (Eigen::VectorXd)
 * @return   The dot product v1.dot(v2).
 * @throws std::invalid_argument if the sizes of v1 and v2 do not match.
 */
double inner(const Eigen::VectorXd& v1, const Eigen::VectorXd& v2);

#endif // EIGEN_NUMPY_BENCHMARK_INNER_H

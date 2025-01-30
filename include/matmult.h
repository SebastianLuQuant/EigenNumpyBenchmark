#ifndef EIGEN_NUMPY_BENCHMARK_MATMUL_H
#define EIGEN_NUMPY_BENCHMARK_MATMUL_H

#include <Eigen/Dense>
#include <stdexcept>

/**
 * @brief Perform a 2D matrix multiplication similar to numpy.matmult.
 *
 * @param A The left operand (Eigen::MatrixXd)
 * @param B The right operand (Eigen::MatrixXd)
 * @return  The product of A * B, as an Eigen::MatrixXd.
 * @throws std::invalid_argument if the dimensions are not compatible for multiplication.
 */
Eigen::MatrixXd matmult(const Eigen::MatrixXd& A,
                       const Eigen::MatrixXd& B);

#endif // EIGEN_NUMPY_BENCHMARK_MATMUL_H

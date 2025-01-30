#ifndef EIGEN_NUMPY_BENCHMARK_ROT90_H
#define EIGEN_NUMPY_BENCHMARK_ROT90_H

#include <Eigen/Dense>
#include <stdexcept>

/**
 * @brief Rotate a 2D matrix by 90*k degrees, counterclockwise.
 *
 * Mimics numpy.rot90(mat, k=1). 
 * k is typically taken modulo 4, so k=1 => 90°, k=2 => 180°, etc.
 *
 * @param mat  The input matrix (2D).
 * @param k    How many times to rotate 90 degrees counterclockwise.
 * @return     A new Eigen::MatrixXd representing the rotated matrix.
 */
Eigen::MatrixXd rot90(const Eigen::MatrixXd& mat, int k=1);

#endif // EIGEN_NUMPY_BENCHMARK_ROT90_H

#include "matmul.h"

Eigen::MatrixXd matmul(const Eigen::MatrixXd& A,
                       const Eigen::MatrixXd& B)
{
    // Check dimension compatibility
    if (A.cols() != B.rows()) {
        throw std::invalid_argument("matmul(): Dimension mismatch. A.cols() must match B.rows().");
    }

    // Eigen's operator* will do the matrix multiplication.
    // For large matrices, this is often quite optimized.
    return A * B;
}

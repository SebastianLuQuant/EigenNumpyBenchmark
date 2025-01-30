#include "concat.h"

Eigen::MatrixXd concat(const std::vector<Eigen::MatrixXd>& matrices, int axis)
{
    if (matrices.empty()) {
        // We might decide to return an empty matrix or throw.
        // Let's return a 0x0 matrix for now.
        return Eigen::MatrixXd(0,0);
    }

    if (axis < 0 || axis > 1) {
        throw std::invalid_argument("concat(): axis must be 0 or 1");
    }

    // Check dimension consistency
    // 1) If axis=0, all matrices must have same number of cols.
    // 2) If axis=1, all matrices must have same number of rows.

    // For convenience, take the first matrix as reference
    auto refRows = matrices[0].rows();
    auto refCols = matrices[0].cols();

    // Calculate total shape
    int totalRows = refRows;
    int totalCols = refCols;

    for (size_t i = 1; i < matrices.size(); ++i) {
        if (axis == 0) {
            // row-wise => same cols
            if (matrices[i].cols() != refCols) {
                throw std::invalid_argument("concat(): dimension mismatch on cols for row-wise concatenation");
            }
            totalRows += matrices[i].rows();
        } else {
            // axis=1 => col-wise => same rows
            if (matrices[i].rows() != refRows) {
                throw std::invalid_argument("concat(): dimension mismatch on rows for column-wise concatenation");
            }
            totalCols += matrices[i].cols();
        }
    }

    // Now create result with totalRows x totalCols
    Eigen::MatrixXd result(totalRows, totalCols);

    // Fill result
    int currentRow = 0;
    int currentCol = 0;

    for (size_t i = 0; i < matrices.size(); ++i) {
        auto& M = matrices[i];
        if (axis == 0) {
            // row-wise: place M in [currentRow..currentRow+M.rows()-1], all columns
            result.block(currentRow, 0, M.rows(), refCols) = M;
            currentRow += M.rows();
        } else {
            // axis=1 => column-wise
            result.block(0, currentCol, refRows, M.cols()) = M;
            currentCol += M.cols();
        }
    }

    return result;
}

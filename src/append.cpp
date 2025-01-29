#include "append.h"

Eigen::MatrixXd append(const Eigen::MatrixXd& base,
                       const Eigen::MatrixXd& values,
                       int axis)
{
    // Axis check
    if (axis < 0 || axis > 1) {
        throw std::invalid_argument("append(): axis must be 0 or 1");
    }

    // Row-wise (axis=0)
    if (axis == 0) {
        if (base.cols() != values.cols()) {
            throw std::invalid_argument("append(): dimension mismatch for row-wise concatenation");
        }
        Eigen::MatrixXd result(base.rows() + values.rows(), base.cols());
        result << base, values;
        return result;
    }
    // Column-wise (axis=1)
    else {
        if (base.rows() != values.rows()) {
            throw std::invalid_argument("append(): dimension mismatch for column-wise concatenation");
        }
        Eigen::MatrixXd result(base.rows(), base.cols() + values.cols());
        result << base, values;
        return result;
    }
}

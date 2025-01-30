#include "inner.h"

double inner(const Eigen::VectorXd& v1, const Eigen::VectorXd& v2)
{
    if (v1.size() != v2.size()) {
        throw std::invalid_argument("inner(): vectors must have the same size");
    }
    return v1.dot(v2);
}

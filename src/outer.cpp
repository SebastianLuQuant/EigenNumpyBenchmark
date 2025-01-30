#include "outer.h"

Eigen::MatrixXd outer(const Eigen::VectorXd& v1, const Eigen::VectorXd& v2)
{
    // The outer product always produces (v1.size() x v2.size())
    // There's typically no dimension mismatch scenario here, so no need to throw.
    // But you could check if either vector is empty, etc., if that matters.
    
    // We can simply do v1 * v2.transpose() (which yields a (n x 1) * (1 x m) => (n x m)).
    return v1 * v2.transpose();
}

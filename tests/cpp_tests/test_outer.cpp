#include <iostream>
#include <cassert>
#include <Eigen/Dense>
#include "outer.h"

int main() {
    std::cout << "[Test] outer function\n";

    // Create two 1D vectors
    Eigen::VectorXd a(2);
    a << 1.0, 2.0; // shape (2, )
    Eigen::VectorXd b(3);
    b << 10.0, 20.0, 30.0; // shape (3, )

    // outer(a, b) => (2 x 3) matrix
    Eigen::MatrixXd outMat = outer(a, b);
    // Check dimensions
    assert(outMat.rows() == 2);
    assert(outMat.cols() == 3);
    // outMat =
    // [1*10   1*20   1*30]
    // [2*10   2*20   2*30]
    // => [10, 20, 30
    //     20, 40, 60]
    assert(outMat(0,0) == 10.0);
    assert(outMat(0,1) == 20.0);
    assert(outMat(1,2) == 60.0);

    std::cout << "[Test] outer function: ALL TESTS PASSED.\n";
    return 0;
}

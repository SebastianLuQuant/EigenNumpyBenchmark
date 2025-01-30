#include <iostream>
#include <cassert>
#include <Eigen/Dense>
#include "matmult.h"

int main() {
    std::cout << "[Test] matmult function\n";

    // Simple 2x3 * 3x2
    Eigen::MatrixXd A(2, 3);
    A << 1, 2, 3,
         4, 5, 6;
    Eigen::MatrixXd B(3, 2);
    B << 1, 4,
         2, 5,
         3, 6;

    // Expected result is a 2x2 matrix
    // [ 1*1 + 2*2 + 3*3, 1*4 + 2*5 + 3*6 ]
    // [ 4*1 + 5*2 + 6*3, 4*4 + 5*5 + 6*6 ]
    // => [14, 32]
    //    [32, 77]

    Eigen::MatrixXd result = matmult(A, B);

    assert(result.rows() == 2);
    assert(result.cols() == 2);
    assert(result(0,0) == 14);
    assert(result(0,1) == 32);
    assert(result(1,0) == 32);
    assert(result(1,1) == 77);

    std::cout << "Basic multiplication passed.\n";

    // Test dimension mismatch
    bool exceptionThrown = false;
    try {
        // A is 2x3, B is 3x2 => that works
        // But if we pass a 2x2?
        Eigen::MatrixXd C(2,2);
        C.setRandom();
        auto shouldFail = matmult(A, C);
    } catch (const std::invalid_argument& e) {
        exceptionThrown = true;
        std::cout << "Caught expected exception: " << e.what() << "\n";
    }
    assert(exceptionThrown);

    std::cout << "[Test] matmult function: ALL TESTS PASSED.\n";
    return 0;
}

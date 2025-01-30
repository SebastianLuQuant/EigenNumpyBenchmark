#include <iostream>
#include <cassert>
#include <Eigen/Dense>
#include "concat.h"

int main() {
    std::cout << "[Test] concat function\n";

    // Prepare sample matrices
    Eigen::MatrixXd A(2, 2);
    A << 1, 2,
         3, 4;

    Eigen::MatrixXd B(3, 2);
    B << 5, 6,
         7, 8,
         9, 10;

    // row-wise concat: A is 2x2, B is 3x2 => total should be 5x2
    std::vector<Eigen::MatrixXd> rowMats = {A, B};
    Eigen::MatrixXd rowResult = concat(rowMats, 0);
    assert(rowResult.rows() == 5);
    assert(rowResult.cols() == 2);
    // Check some values
    assert(rowResult(0,0) == 1);
    assert(rowResult(1,1) == 4);
    assert(rowResult(2,0) == 5);
    assert(rowResult(4,1) == 10);

    std::cout << "Row-wise concat passed.\n";

    // col-wise concat: A is 2x2, let's make another 2x3
    Eigen::MatrixXd C(2, 3);
    C << 10, 11, 12,
         13, 14, 15;

    std::vector<Eigen::MatrixXd> colMats = {A, C};
    Eigen::MatrixXd colResult = concat(colMats, 1);
    assert(colResult.rows() == 2);
    assert(colResult.cols() == 5);
    // Check some values
    // Original A:
    assert(colResult(0,0) == 1);
    assert(colResult(1,1) == 4);
    // Then from C in columns 2..4
    assert(colResult(0,2) == 10);
    assert(colResult(1,4) == 15);

    std::cout << "Column-wise concat passed.\n";

    // dimension mismatch scenario
    bool exceptionThrown = false;
    Eigen::MatrixXd D(2, 2);
    D.setRandom();
    std::vector<Eigen::MatrixXd> mismatch = {A, D, B}; 
    // B has 3 rows, while A and D have 2 => row mismatch for row-wise
    try {
        auto failResult = concat(mismatch, 1);
    } catch(const std::invalid_argument& e) {
        exceptionThrown = true;
        std::cout << "Caught expected exception: " << e.what() << "\n";
    }
    assert(exceptionThrown);

    std::cout << "[Test] concat function: ALL TESTS PASSED.\n";
    return 0;
}

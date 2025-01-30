#include <iostream>
#include <cassert>
#include <Eigen/Dense>
#include "rot90.h"

int main() {
    Eigen::MatrixXd M(2, 3);
    M << 1, 2, 3,
         4, 5, 6;
    // M =
    // [1, 2, 3
    //  4, 5, 6]

    // k=1 => shape => 3x2
    // Expect => [4, 1
    //            5, 2
    //            6, 3]
    Eigen::MatrixXd r1 = rot90(M, 1);
    assert(r1.rows() == 3 && r1.cols() == 2);
    assert(r1(0,0) == 4 && r1(2,1) == 3);

    // k=2 => shape => 2x3
    // Expect => [6, 5, 4
    //            3, 2, 1]
    Eigen::MatrixXd r2 = rot90(M, 2);
    assert(r2(0,0) == 6 && r2(1,2) == 1);

    // k=3 => shape => 3x2
    // Expect => [3, 6
    //            2, 5
    //            1, 4]
    Eigen::MatrixXd r3 = rot90(M, 3);
    assert(r3.rows() == 3 && r3.cols() == 2);
    assert(r3(0,0) == 3 && r3(2,1) == 4);

    // negative k => e.g. k=-1 => same as k=3
    Eigen::MatrixXd rn = rot90(M, -1);
    // compare with r3
    assert((rn - r3).norm() < 1e-12);

    std::cout << "[Test] rot90 function: ALL TESTS PASSED.\n";
    return 0;
}

#include <iostream>
#include <cassert>
#include <Eigen/Dense>
#include "append.h"

int main() {
    std::cout << "[Test] append function with exceptions\n";
    Eigen::MatrixXd A(2,2), B(1,2);
    A << 1,2, 3,4;
    B << 5,6;

    // Normal case
    auto appended = append(A, B, 0);
    assert(appended.rows() == 3);

    // Now test mismatch
    Eigen::MatrixXd C(1,3); // mismatch with A
    bool exceptionThrown = false;
    try {
        auto failCase = append(A, C, 0);
    } catch(const std::invalid_argument& e) {
        exceptionThrown = true;
        std::cout << "Caught expected std::invalid_argument: " << e.what() << "\n";
    }
    assert(exceptionThrown);

    std::cout << "[Test] all checks passed.\n";
    return 0;
}

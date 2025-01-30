#include <iostream>
#include <cassert>
#include <Eigen/Dense>
#include "inner.h"

int main() {
    std::cout << "[Test] inner function\n";

    // Create two 1D vectors
    Eigen::VectorXd x(3);
    x << 1.0, 2.0, 3.0;
    Eigen::VectorXd y(3);
    y << 4.0, 5.0, 6.0;

    double result = inner(x, y);
    // Expected dot product = 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    assert(result == 32.0);
    std::cout << "Basic dot product passed.\n";

    // Mismatch scenario
    bool exceptionThrown = false;
    Eigen::VectorXd z(2);
    z << 10.0, 20.0;
    try {
        auto failVal = inner(x, z);
    } catch (const std::invalid_argument& e) {
        exceptionThrown = true;
        std::cout << "Caught expected exception: " << e.what() << "\n";
    }
    assert(exceptionThrown);

    std::cout << "[Test] inner function: ALL TESTS PASSED.\n";
    return 0;
}

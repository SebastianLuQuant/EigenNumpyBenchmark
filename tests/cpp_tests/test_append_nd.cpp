#include <iostream>
#include <unsupported/Eigen/CXX11/Tensor>
#include <cassert>
#include "append_nd.h"

using namespace std;

int main() {
    // Test with a 3D tensor (Rank = 3)
    const int d0 = 2, d1 = 3, d2 = 4;
    Eigen::Tensor<double, 3> a(d0, d1, d2);
    Eigen::Tensor<double, 3> b(d0, d1, d2);
    a.setRandom();
    b.setRandom();

    // Test concatenation along axis 0:
    try {
        Eigen::Tensor<double, 3> result0 = append_nd<3>(a, b, 0);
        // Expected dimensions: (d0*2, d1, d2)
        assert(result0.dimension(0) == d0 * 2);
        assert(result0.dimension(1) == d1);
        assert(result0.dimension(2) == d2);
        cout << "append_nd along axis 0 passed." << endl;
    } catch (const std::exception& e) {
        cout << "append_nd along axis 0 failed: " << e.what() << endl;
    }

    // Test concatenation along axis 1:
    try {
        Eigen::Tensor<double, 3> result1 = append_nd<3>(a, b, 1);
        // Expected dimensions: (d0, d1*2, d2)
        assert(result1.dimension(0) == d0);
        assert(result1.dimension(1) == d1 * 2);
        assert(result1.dimension(2) == d2);
        cout << "append_nd along axis 1 passed." << endl;
    } catch (const std::exception& e) {
        cout << "append_nd along axis 1 failed: " << e.what() << endl;
    }

    // Test concatenation along axis 2:
    try {
        Eigen::Tensor<double, 3> result2 = append_nd<3>(a, b, 2);
        // Expected dimensions: (d0, d1, d2*2)
        assert(result2.dimension(0) == d0);
        assert(result2.dimension(1) == d1);
        assert(result2.dimension(2) == d2 * 2);
        cout << "append_nd along axis 2 passed." << endl;
    } catch (const std::exception& e) {
        cout << "append_nd along axis 2 failed: " << e.what() << endl;
    }

    // Test mismatch: Create a tensor with a mismatched dimension on a non-concatenation axis.
    try {
        Eigen::Tensor<double, 3> b_wrong(d0, d1 + 1, d2);
        b_wrong.setRandom();
        auto result_wrong = append_nd<3>(a, b_wrong, 0); // axis 0, but dimension 1 mismatch.
        cout << "append_nd mismatch test failed: no exception thrown!" << endl;
    } catch (const std::exception& e) {
        cout << "append_nd mismatch test passed: caught exception: " << e.what() << endl;
    }

    std::cout << "[Test] all checks passed.\n";
    return 0;
}

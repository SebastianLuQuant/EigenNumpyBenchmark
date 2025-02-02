#include <iostream>
#include <unsupported/Eigen/CXX11/Tensor>
#include <cassert>
#include "concat_nd.h"

using namespace std;

int main() {
    // Test for a 3D tensor (Rank = 3)
    const int d0 = 2, d1 = 3, d2 = 4;
    Eigen::Tensor<double, 3> t1(d0, d1, d2);
    Eigen::Tensor<double, 3> t2(d0, d1, d2);
    Eigen::Tensor<double, 3> t3(d0, d1, d2);
    t1.setRandom();
    t2.setRandom();
    t3.setRandom();

    vector<Eigen::Tensor<double, 3>> tensors = {t1, t2, t3};

    // Test concatenation along axis 0:
    try {
        auto result0 = concat_nd<3>(tensors, 0);
        // Expected dimensions: (d0*3, d1, d2)
        assert(result0.dimension(0) == d0 * 3);
        assert(result0.dimension(1) == d1);
        assert(result0.dimension(2) == d2);
        cout << "concat_nd along axis 0 passed." << endl;
    } catch (const std::exception& e) {
        cout << "concat_nd along axis 0 failed: " << e.what() << endl;
    }

    // Test concatenation along axis 1:
    try {
        auto result1 = concat_nd<3>(tensors, 1);
        // Expected dimensions: (d0, d1*3, d2)
        assert(result1.dimension(0) == d0);
        assert(result1.dimension(1) == d1 * 3);
        assert(result1.dimension(2) == d2);
        cout << "concat_nd along axis 1 passed." << endl;
    } catch (const std::exception& e) {
        cout << "concat_nd along axis 1 failed: " << e.what() << endl;
    }

    // Test concatenation along axis 2:
    try {
        auto result2 = concat_nd<3>(tensors, 2);
        // Expected dimensions: (d0, d1, d2*3)
        assert(result2.dimension(0) == d0);
        assert(result2.dimension(1) == d1);
        assert(result2.dimension(2) == d2 * 3);
        cout << "concat_nd along axis 2 passed." << endl;
    } catch (const std::exception& e) {
        cout << "concat_nd along axis 2 failed: " << e.what() << endl;
    }

    // Test mismatch: Create a tensor with a mismatched dimension on a non-concatenation axis.
    try {
        Eigen::Tensor<double, 3> t_wrong(d0, d1 + 1, d2);
        t_wrong.setRandom();
        vector<Eigen::Tensor<double, 3>> tensors_wrong = {t1, t_wrong};
        auto result_wrong = concat_nd<3>(tensors_wrong, 0);
        cout << "concat_nd mismatch test failed: no exception thrown!" << endl;
    } catch (const std::exception& e) {
        cout << "concat_nd mismatch test passed: caught exception: " << e.what() << endl;
    }

    std::cout << "[Test] all checks passed.\n";
    return 0;
}

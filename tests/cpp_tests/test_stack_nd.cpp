#include <iostream>
#include <unsupported/Eigen/CXX11/Tensor>
#include <cassert>
#include "stack_nd.h"

using namespace std;

int main() {
    // Test with Rank = 2 (i.e., 2D matrices) -> resulting tensor should be 3D.
    const int rows = 3, cols = 4;
    Eigen::Tensor<double, 2> a(rows, cols);
    Eigen::Tensor<double, 2> b(rows, cols);
    a.setRandom();
    b.setRandom();

    vector<Eigen::Tensor<double, 2>> tensors = {a, b};

    // Test stacking along axis 0: result shape should be (2, rows, cols)
    try {
        auto result0 = stack_nd<2>(tensors, 0);
        assert(result0.dimension(0) == 2);
        assert(result0.dimension(1) == rows);
        assert(result0.dimension(2) == cols);
        cout << "stack_nd along axis 0 passed." << endl;
    } catch (const std::exception& e) {
        cout << "stack_nd along axis 0 failed: " << e.what() << endl;
    }

    // Test stacking along axis 1: result shape should be (rows, 2, cols)
    try {
        auto result1 = stack_nd<2>(tensors, 1);
        assert(result1.dimension(0) == rows);
        assert(result1.dimension(1) == 2);
        assert(result1.dimension(2) == cols);
        cout << "stack_nd along axis 1 passed." << endl;
    } catch (const std::exception& e) {
        cout << "stack_nd along axis 1 failed: " << e.what() << endl;
    }

    // Test stacking along axis 2: result shape should be (rows, cols, 2)
    try {
        auto result2 = stack_nd<2>(tensors, 2);
        assert(result2.dimension(0) == rows);
        assert(result2.dimension(1) == cols);
        assert(result2.dimension(2) == 2);
        cout << "stack_nd along axis 2 passed." << endl;
    } catch (const std::exception& e) {
        cout << "stack_nd along axis 2 failed: " << e.what() << endl;
    }

    // Test mismatch: create a tensor with different dimensions.
    try {
        Eigen::Tensor<double, 2> b_wrong(rows, cols + 1);
        b_wrong.setRandom();
        vector<Eigen::Tensor<double, 2>> tensors_wrong = {a, b_wrong};
        auto result_wrong = stack_nd<2>(tensors_wrong, 0);
        cout << "stack_nd mismatch test failed: no exception thrown!" << endl;
    } catch (const std::exception& e) {
        cout << "stack_nd mismatch test passed: caught exception: " << e.what() << endl;
    }

    std::cout << "[Test] all checks passed.\n";

    return 0;
}

// tests/benchmark_eigen.cpp
#include <iostream>
#include <chrono>
#include <vector>
#include <functional>
#include <cassert>
#include <string>
#include <Eigen/Dense>

// Include your Eigen wrapper function headers
#include "matmult.h"
#include "append.h"
#include "concat.h"
#include "inner.h"
#include "outer.h"
#include "rot90.h"

using namespace std;
using namespace std::chrono;
using Eigen::MatrixXd;
using Eigen::VectorXd;

// ScopedTimer: uses RAII to measure elapsed time in seconds.
// When an object goes out of scope, it writes the elapsed time into a reference variable.
class ScopedTimer {
public:
    ScopedTimer(double& result, const std::string& name = "")
        : result_ref(result), name(name), start(steady_clock::now()) { }
    ~ScopedTimer() {
        auto end = steady_clock::now();
        result_ref = duration<double>(end - start).count();
        // Optionally, you can print the elapsed time here.
        // std::cout << "Timer [" << name << "] elapsed: " << result_ref << " sec" << std::endl;
    }
private:
    double& result_ref;
    std::string name;
    time_point<steady_clock> start;
};

// Template function to benchmark any callable 'func' with arguments 'args'.
// It runs the function 'iterations' times, using ScopedTimer in each iteration, and returns the average time.
template<typename Func, typename... Args>
double benchmark_with_scoped_timer(Func func, int iterations, Args&&... args) {
    double total = 0.0;
    for (int i = 0; i < iterations; ++i) {
        double elapsed = 0.0;
        {
            ScopedTimer timer(elapsed, "Iteration");
            func(std::forward<Args>(args)...);
        }
        total += elapsed;
    }
    return total / iterations;
}

int main() {
    // Define test sizes: from small to large.
    vector<int> sizes = {10, 50, 100, 500, 1000, 2000, 5000};

    // For reproducibility, you might fix a random seed (here we print a notice; in production, use srand or Eigen's method).
    srand(12345);

    cout << "C++ Benchmark Results for Eigen Wrapper Functions (using ScopedTimer):" << endl;

    // 1. Benchmark Matrix Multiplication (matmult)
    cout << "\nFunction: matmult" << endl;
    for (int size : sizes) {
        MatrixXd A = MatrixXd::Random(size, size);
        MatrixXd B = MatrixXd::Random(size, size);
        double avgTime = benchmark_with_scoped_timer(matmult, 10, A, B);
        cout << "Size: " << size << "x" << size 
             << "\tAverage Time: " << avgTime << " sec" << endl;
    }

    // 2. Benchmark Append (row-wise, axis=0)
    cout << "\nFunction: append (row-wise, axis=0)" << endl;
    for (int size : sizes) {
        MatrixXd X = MatrixXd::Random(size, size);
        MatrixXd Y = MatrixXd::Random(size, size);
        double avgTime = benchmark_with_scoped_timer(append, 10, X, Y, 0);
        cout << "Size: " << size << "x" << size 
             << "\tAverage Time: " << avgTime << " sec" << endl;
    }

    // 3. Benchmark Concat (row-wise, axis=0)
    cout << "\nFunction: concat (row-wise, axis=0)" << endl;
    for (int size : sizes) {
        MatrixXd A = MatrixXd::Random(size, size);
        MatrixXd B = MatrixXd::Random(size, size);
        MatrixXd C = MatrixXd::Random(size, size);
        vector<MatrixXd> mats = {A, B, C};
        double avgTime = benchmark_with_scoped_timer(concat, 10, mats, 0);
        cout << "Size: " << size << "x" << size 
             << "\tAverage Time: " << avgTime << " sec" << endl;
    }

    // 4. Benchmark Inner (1D dot product)
    cout << "\nFunction: inner (1D dot product)" << endl;
    for (int size : sizes) {
        VectorXd v1 = VectorXd::Random(size);
        VectorXd v2 = VectorXd::Random(size);
        double avgTime = benchmark_with_scoped_timer(inner, 10000, v1, v2);
        cout << "Vector Size: " << size 
             << "\tAverage Time: " << avgTime << " sec" << endl;
    }

    // 5. Benchmark Outer (1D outer product)
    cout << "\nFunction: outer (1D outer product)" << endl;
    for (int size : sizes) {
        VectorXd v1 = VectorXd::Random(size);
        VectorXd v2 = VectorXd::Random(size);
        double avgTime = benchmark_with_scoped_timer(outer, 10000, v1, v2);
        cout << "Vector Size: " << size 
             << "\tAverage Time: " << avgTime << " sec" << endl;
    }

    // 6. Benchmark Rot90 (rotate matrix by 90 degrees)
    cout << "\nFunction: rot90 (rotate matrix by 90°)" << endl;
    for (int size : sizes) {
        MatrixXd M = MatrixXd::Random(size, size);
        double avgTime = benchmark_with_scoped_timer(rot90, 100, M, 1);
        cout << "Size: " << size << "x" << size 
             << "\tAverage Time: " << avgTime << " sec" << endl;
    }

    return 0;
}

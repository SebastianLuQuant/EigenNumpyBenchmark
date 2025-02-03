#include <iostream>
#include <vector>
#include <complex>
#include <cassert>
#include "fft.h"

using namespace std;

int main() {
    // Test case: delta impulse.
    // For a delta impulse (input[0] = 1, rest 0), the FFT should yield all ones (1+0i) ideally.
    const int N = 8;
    std::vector<double> input(N, 0.0);
    input[0] = 1.0; // Delta impulse

    std::vector<std::complex<double>> output = fft(input);
    
    // Check that each FFT output element is approximately 1+0i.
    for (int i = 0; i < N; i++) {
        std::complex<double> expected(1.0, 0.0);
        if (std::abs(output[i] - expected) > 1e-6) {
            std::cerr << "FFT output mismatch at index " << i << std::endl;
            return 1;
        }
    }
    
    std::cout << "FFT test passed." << std::endl;
    return 0;
}

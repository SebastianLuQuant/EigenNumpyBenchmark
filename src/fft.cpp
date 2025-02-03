#include "fft.h"
#include <unsupported/Eigen/FFT>

std::vector<std::complex<double>> fft(const std::vector<double>& input) {
    Eigen::FFT<double> fft_obj;
    std::vector<std::complex<double>> output;
    fft_obj.fwd(output, input);  // Compute forward FFT
    return output;
}

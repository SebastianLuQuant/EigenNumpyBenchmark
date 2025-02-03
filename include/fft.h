#ifndef FFT_H
#define FFT_H

#include <vector>
#include <complex>

/**
 * @brief Compute the 1D Fast Fourier Transform (FFT) of a real-valued input vector.
 *
 * This function computes the discrete Fourier transform using Eigen's FFT module.
 * It accepts a std::vector<double> as input and returns a std::vector<std::complex<double>>
 * representing the FFT result, similar to numpy.fft.fft.
 *
 * @param input A vector of real numbers (double).
 * @return A vector of std::complex<double> containing the FFT output.
 */
std::vector<std::complex<double>> fft(const std::vector<double>& input);

#endif // FFT_H

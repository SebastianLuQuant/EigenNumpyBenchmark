#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <vector>
#include <stdexcept>
#include <Eigen/Dense>

// 你的函数声明头
#include "append.h"
#include "concat.h"
#include "inner.h"
#include "outer.h"
#include "matmult.h"
#include "rot90.h"

namespace py = pybind11;

/**
 * @brief Convert a 2D NumPy array to Eigen::MatrixXd.
 *        Throws std::runtime_error if `arr` isn't 2D.
 */
Eigen::MatrixXd numpy_to_eigen_2d(const py::array_t<double>& arr) {
    py::buffer_info buf = arr.request();
    if (buf.ndim != 2) {
        throw std::runtime_error("Expected a 2D array.");
    }
    int rows = static_cast<int>(buf.shape[0]);
    int cols = static_cast<int>(buf.shape[1]);
    Eigen::MatrixXd mat(rows, cols);

    double* ptr = static_cast<double*>(buf.ptr);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            mat(r, c) = ptr[r * cols + c];
        }
    }
    return mat;
}

/**
 * @brief Convert Eigen::MatrixXd back to a NumPy 2D array.
 */
py::array_t<double> eigen_to_numpy_2d(const Eigen::MatrixXd& mat) {
    py::array_t<double> arr({mat.rows(), mat.cols()});
    py::buffer_info buf = arr.request();
    double* ptr = static_cast<double*>(buf.ptr);
    for (int r = 0; r < mat.rows(); ++r) {
        for (int c = 0; c < mat.cols(); ++c) {
            ptr[r * mat.cols() + c] = mat(r, c);
        }
    }
    return arr;
}

/**
 * @brief Convert a 1D NumPy array to Eigen::VectorXd.
 *        Throws std::runtime_error if `arr` isn't 1D.
 */
Eigen::VectorXd numpy_to_eigen_1d(const py::array_t<double>& arr) {
    py::buffer_info buf = arr.request();
    if (buf.ndim != 1) {
        throw std::runtime_error("Expected a 1D array.");
    }
    int size = static_cast<int>(buf.shape[0]);
    Eigen::VectorXd vec(size);

    double* ptr = static_cast<double*>(buf.ptr);
    for (int i = 0; i < size; ++i) {
        vec(i) = ptr[i];
    }
    return vec;
}

/**
 * @brief Convert a list of 2D NumPy arrays to a std::vector<Eigen::MatrixXd>.
 */
std::vector<Eigen::MatrixXd> list_of_2d_arrays_to_eigen(
    const py::list& list_in)
{
    std::vector<Eigen::MatrixXd> result;
    for (auto item : list_in) {
        // Convert each element to py::array_t<double> then to MatrixXd
        py::array_t<double> arr = py::cast<py::array_t<double>>(item);
        result.push_back(numpy_to_eigen_2d(arr));
    }
    return result;
}

/**
 * @brief Python wrapper for `append(base, values, axis)`.
 */
py::array_t<double> py_append(py::array_t<double> base,
                              py::array_t<double> values,
                              int axis)
{
    Eigen::MatrixXd b = numpy_to_eigen_2d(base);
    Eigen::MatrixXd v = numpy_to_eigen_2d(values);
    Eigen::MatrixXd out = append(b, v, axis);
    return eigen_to_numpy_2d(out);
}

/**
 * @brief Python wrapper for `concat(matrices, axis)`.
 *        Expects a Python list of 2D arrays.
 */
py::array_t<double> py_concat(py::list arr_list, int axis)
{
    std::vector<Eigen::MatrixXd> mats = list_of_2d_arrays_to_eigen(arr_list);
    Eigen::MatrixXd out = concat(mats, axis);
    return eigen_to_numpy_2d(out);
}

/**
 * @brief Python wrapper for `matmult(A, B)`.
 */
py::array_t<double> py_matmult(py::array_t<double> A,
                               py::array_t<double> B)
{
    Eigen::MatrixXd a = numpy_to_eigen_2d(A);
    Eigen::MatrixXd b = numpy_to_eigen_2d(B);
    Eigen::MatrixXd out = matmult(a, b);
    return eigen_to_numpy_2d(out);
}

/**
 * @brief Python wrapper for `inner(v1, v2)`.
 */
double py_inner(py::array_t<double> v1,
                py::array_t<double> v2)
{
    Eigen::VectorXd x = numpy_to_eigen_1d(v1);
    Eigen::VectorXd y = numpy_to_eigen_1d(v2);
    return inner(x, y);
}

/**
 * @brief Python wrapper for `outer(v1, v2)`.
 */
py::array_t<double> py_outer(py::array_t<double> v1,
                             py::array_t<double> v2)
{
    Eigen::VectorXd x = numpy_to_eigen_1d(v1);
    Eigen::VectorXd y = numpy_to_eigen_1d(v2);
    Eigen::MatrixXd out = outer(x, y);
    return eigen_to_numpy_2d(out);
}

/**
 * @brief Python wrapper for `rot90(input, k)`.
 */
py::array_t<double> py_rot90(py::array_t<double> matrix,
                             int k)
{
    Eigen::MatrixXd m = numpy_to_eigen_2d(matrix);
    Eigen::MatrixXd out = rot90(m, k);
    return eigen_to_numpy_2d(out);
}

/**
 * @brief The module definition
 */
PYBIND11_MODULE(MyPyEigen, m) {
    m.doc() = "Python bindings for C++ Eigen-based functions";

    m.def("append",   &py_append,   "Append two 2D matrices along an axis");
    m.def("concat",   &py_concat,   "Concatenate multiple 2D matrices along an axis");
    m.def("matmult",  &py_matmult,  "Matrix multiplication (2D)");
    m.def("inner",    &py_inner,    "1D vector inner product");
    m.def("outer",    &py_outer,    "1D vector outer product");
    m.def("rot90",    &py_rot90,    "Rotate a 2D matrix by k * 90 degrees");
}

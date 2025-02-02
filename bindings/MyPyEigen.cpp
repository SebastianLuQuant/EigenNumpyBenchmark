#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <vector>
#include <stdexcept>
#include <Eigen/Dense>

// Include 2D interfaces
#include "append.h"
#include "concat.h"
#include "inner.h"
#include "outer.h"
#include "matmult.h"
#include "rot90.h"

// Include ND interfaces
#include "append_nd.h"
#include "concat_nd.h"
#include "stack_nd.h"  // This file should include (and internally include) concat_nd.h

namespace py = pybind11;

/* ----------------- 2D Conversion Functions ----------------- */
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

/* ----------------- ND Conversion Functions ----------------- */
/**
 * @brief Convert a 3D NumPy array to Eigen::Tensor<double, 3>.
 */
Eigen::Tensor<double, 3> numpy_to_eigen_3d(const py::array_t<double>& arr) {
    py::buffer_info buf = arr.request();
    if (buf.ndim != 3) {
        throw std::runtime_error("Expected a 3D array.");
    }
    Eigen::Tensor<double, 3> tensor(buf.shape[0], buf.shape[1], buf.shape[2]);
    double* ptr = static_cast<double*>(buf.ptr);
    for (ssize_t i = 0; i < buf.shape[0]; ++i)
        for (ssize_t j = 0; j < buf.shape[1]; ++j)
            for (ssize_t k = 0; k < buf.shape[2]; ++k)
                tensor(i, j, k) = ptr[i * (buf.shape[1] * buf.shape[2]) + j * buf.shape[2] + k];
    return tensor;
}

/**
 * @brief Convert Eigen::Tensor<double, 3> back to a NumPy 3D array.
 */
py::array_t<double> eigen_to_numpy_3d(const Eigen::Tensor<double, 3>& tensor) {
    std::vector<ssize_t> shape = { static_cast<ssize_t>(tensor.dimension(0)),
                                   static_cast<ssize_t>(tensor.dimension(1)),
                                   static_cast<ssize_t>(tensor.dimension(2)) };
    py::array_t<double> arr(shape);
    py::buffer_info buf = arr.request();
    double* ptr = static_cast<double*>(buf.ptr);
    for (int i = 0; i < tensor.dimension(0); ++i)
        for (int j = 0; j < tensor.dimension(1); ++j)
            for (int k = 0; k < tensor.dimension(2); ++k)
                ptr[i * (tensor.dimension(1)*tensor.dimension(2)) + j * tensor.dimension(2) + k] = tensor(i, j, k);
    return arr;
}

/**
 * @brief Helper function: Convert Eigen::MatrixXd to Eigen::Tensor<double, 2>.
 */
Eigen::Tensor<double, 2> matrix_to_tensor(const Eigen::MatrixXd& mat) {
    Eigen::Tensor<double, 2> t(mat.rows(), mat.cols());
    for (int i = 0; i < mat.rows(); ++i)
        for (int j = 0; j < mat.cols(); ++j)
            t(i, j) = mat(i, j);
    return t;
}

/* ----------------- 2D Python Wrappers ----------------- */

py::array_t<double> py_append(py::array_t<double> base,
                              py::array_t<double> values,
                              int axis) {
    Eigen::MatrixXd b = numpy_to_eigen_2d(base);
    Eigen::MatrixXd v = numpy_to_eigen_2d(values);
    Eigen::MatrixXd out = append(b, v, axis);
    return eigen_to_numpy_2d(out);
}

py::array_t<double> py_concat(py::list arr_list, int axis) {
    std::vector<Eigen::MatrixXd> mats;
    for (auto item : arr_list) {
        py::array_t<double> arr = py::cast<py::array_t<double>>(item);
        mats.push_back(numpy_to_eigen_2d(arr));
    }
    Eigen::MatrixXd out = concat(mats, axis);
    return eigen_to_numpy_2d(out);
}

py::array_t<double> py_matmult(py::array_t<double> A,
                               py::array_t<double> B) {
    Eigen::MatrixXd a = numpy_to_eigen_2d(A);
    Eigen::MatrixXd b = numpy_to_eigen_2d(B);
    Eigen::MatrixXd out = matmult(a, b);
    return eigen_to_numpy_2d(out);
}

double py_inner(py::array_t<double> v1,
                py::array_t<double> v2) {
    Eigen::VectorXd x = numpy_to_eigen_1d(v1);
    Eigen::VectorXd y = numpy_to_eigen_1d(v2);
    return inner(x, y);
}

py::array_t<double> py_outer(py::array_t<double> v1,
                             py::array_t<double> v2) {
    Eigen::VectorXd x = numpy_to_eigen_1d(v1);
    Eigen::VectorXd y = numpy_to_eigen_1d(v2);
    Eigen::MatrixXd out = outer(x, y);
    return eigen_to_numpy_2d(out);
}

py::array_t<double> py_rot90(py::array_t<double> matrix,
                             int k) {
    Eigen::MatrixXd m = numpy_to_eigen_2d(matrix);
    Eigen::MatrixXd out = rot90(m, k);
    return eigen_to_numpy_2d(out);
}

/* ----------------- ND Python Wrappers ----------------- */

/**
 * @brief Python wrapper for ND append (3D version).
 * Accepts two 3D NumPy arrays and concatenates them along the specified axis.
 */
py::array_t<double> py_append_nd_3(py::array_t<double> a,
                                   py::array_t<double> b,
                                   int axis) {
    Eigen::Tensor<double, 3> A = numpy_to_eigen_3d(a);
    Eigen::Tensor<double, 3> B = numpy_to_eigen_3d(b);
    Eigen::Tensor<double, 3> out = append_nd<3>(A, B, axis);
    return eigen_to_numpy_3d(out);
}

/**
 * @brief Python wrapper for ND concat (3D version).
 * Accepts a Python list of 3D NumPy arrays and concatenates them along the specified axis.
 */
py::array_t<double> py_concat_nd_3(py::list arr_list, int axis) {
    std::vector<Eigen::Tensor<double, 3>> tensors;
    for (auto item : arr_list) {
        py::array_t<double> arr = py::cast<py::array_t<double>>(item);
        tensors.push_back(numpy_to_eigen_3d(arr));
    }
    Eigen::Tensor<double, 3> out = concat_nd<3>(tensors, axis);
    return eigen_to_numpy_3d(out);
}

/**
 * @brief Python wrapper for ND stack (2D inputs).
 * Accepts a Python list of 2D NumPy arrays, converts them to 2D tensors,
 * then stacks them along a new axis (using stack_nd), resulting in a 3D array.
 */
py::array_t<double> py_stack_nd_2(py::list arr_list, int axis) {
    std::vector<Eigen::Tensor<double, 2>> tensors;
    for (auto item : arr_list) {
        py::array_t<double> arr = py::cast<py::array_t<double>>(item);
        // First convert to Eigen::MatrixXd, then convert that to a 2D tensor.
        Eigen::MatrixXd mat = numpy_to_eigen_2d(arr);
        Eigen::Tensor<double, 2> t = matrix_to_tensor(mat);
        tensors.push_back(t);
    }
    // stack_nd for Rank=2 returns an Eigen::Tensor<double, 3>
    Eigen::Tensor<double, 3> out = stack_nd<2>(tensors, axis);
    return eigen_to_numpy_3d(out);
}

/**
 * @brief Module definition.
 */
PYBIND11_MODULE(MyPyEigen, m) {
    m.doc() = "Python bindings for C++ Eigen-based functions";

    // 2D Interfaces
    m.def("append",   &py_append,   "Append two 2D matrices along an axis");
    m.def("concat",   &py_concat,   "Concatenate multiple 2D matrices along an axis");
    m.def("matmult",  &py_matmult,  "Matrix multiplication (2D)");
    m.def("inner",    &py_inner,    "1D vector inner product");
    m.def("outer",    &py_outer,    "1D vector outer product");
    m.def("rot90",    &py_rot90,    "Rotate a 2D matrix by k * 90 degrees");

    // ND Interfaces
    m.def("append_nd", &py_append_nd_3, "Append two 3D arrays along a specified axis");
    m.def("concat_nd", &py_concat_nd_3, "Concatenate a list of 3D arrays along a specified axis");
    m.def("stack_nd",  &py_stack_nd_2,  "Stack a list of 2D arrays along a new axis (resulting in a 3D array)");
}

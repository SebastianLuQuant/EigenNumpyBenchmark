# setup.py

from setuptools import setup, Extension
import pybind11
from pybind11.setup_helpers import Pybind11Extension
import os
import glob

# 收集 src/ 目录下所有 .cpp 文件
cpp_files = glob.glob(os.path.join("..", "src", "*.cpp"))

ext_modules = [
    Pybind11Extension(
        "MyPyEigen",                      # 最终 import 的模块名
        ["MyPyEigen.cpp"] + cpp_files,               # 需要编译的 C++ 源文件
        include_dirs=[
            "../include",              # 你的 append.h, matmult.h
            "../external/eigen",       # Eigen header
            pybind11.get_include()     # pybind11
        ],
        language="c++",
        extra_compile_args=["-std=c++17", "-O3"],
    ),
]

setup(
    name="MyPyEigen",
    version="0.4",
    author="Yichen Lu",
    description="Python bindings for my Eigen-based C++ wrappers, optimized by O3, with N-Dimension operation and fft implemented",
    ext_modules=ext_modules,
    install_requires=["pybind11", "numpy"],
    zip_safe=False,
)

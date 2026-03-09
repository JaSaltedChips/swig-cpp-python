from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "rechner_pybind",
        ["calculator.cpp"],
        cxx_std=11,
    )
]

setup(
    name="rechner_pybind",
    version="1.0",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)

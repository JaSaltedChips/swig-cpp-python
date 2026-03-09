#include <cmath>
#include <pybind11/pybind11.h>

class Calculator {
public:
    double add(double a, double b) {
        return a + b;
    }

    double multiply(double a, double b) {
        return a * b;
    }

    double power(double base, double exponent) {
        return pow(base, exponent);
    }

    double squareRoot(double value) {
        return sqrt(value);
    }
};

namespace py = pybind11;

PYBIND11_MODULE(rechner_pybind, m) {
    m.doc() = "Calculator module using pybind11";

    py::class_<Calculator>(m, "Calculator")
        .def(py::init<>())
        .def("add", &Calculator::add)
        .def("multiply", &Calculator::multiply)
        .def("power", &Calculator::power)
        .def("squareRoot", &Calculator::squareRoot);
}

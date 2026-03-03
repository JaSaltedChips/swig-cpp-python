%module rechner_arrays

%{
#include "calculator.cpp"
%}

%typemap(in) const double [3] (double temp[3]) {
    PyObject* seq = PySequence_Fast($input, "Expected a sequence of 3 floats");
    if (!seq) {
        SWIG_fail;
    }
    if (PySequence_Fast_GET_SIZE(seq) != 3) {
        PyErr_SetString(PyExc_ValueError, "Expected exactly 3 floats");
        Py_DECREF(seq);
        SWIG_fail;
    }
    for (int i = 0; i < 3; ++i) {
        PyObject* item = PySequence_Fast_GET_ITEM(seq, i);
        PyObject* num = PyNumber_Float(item);
        if (!num) {
            Py_DECREF(seq);
            SWIG_fail;
        }
        temp[i] = PyFloat_AsDouble(num);
        Py_DECREF(num);
    }
    Py_DECREF(seq);
    $1 = temp;
}

class Calculator {
public:
    double add(double a, double b);
    double multiply(double a, double b);
    double power(double base, double exponent);
    double squareRoot(double value);
    double sum3(const double values[3]);
};

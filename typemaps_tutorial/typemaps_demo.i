%module typemaps_demo

%{
#include "point.h"
%}

%typemap(in) Point {
    if (!PyDict_Check($input)) {
        PyErr_SetString(PyExc_TypeError, "Point must be a dict with keys 'x' and 'y'");
        SWIG_fail;
    }
    PyObject* xobj = PyDict_GetItemString($input, "x");
    PyObject* yobj = PyDict_GetItemString($input, "y");
    if (!xobj || !yobj || !PyLong_Check(xobj) || !PyLong_Check(yobj)) {
        PyErr_SetString(PyExc_TypeError, "Point dict must contain integer 'x' and 'y'");
        SWIG_fail;
    }
    $1 = Point{static_cast<int>(PyLong_AsLong(xobj)), static_cast<int>(PyLong_AsLong(yobj))};
}

%typemap(out) Point {
    PyObject* dict = PyDict_New();
    PyDict_SetItemString(dict, "x", PyLong_FromLong(result.x));
    PyDict_SetItemString(dict, "y", PyLong_FromLong(result.y));
    resultobj = dict;
}

%include "point.h"

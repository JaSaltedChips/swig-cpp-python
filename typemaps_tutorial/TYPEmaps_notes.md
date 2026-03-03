# Writing SWIG Typemaps (Quick Guide)

This note summarizes how to write SWIG typemaps and includes a checklist.

## Core Idea

A typemap is a small code snippet that tells SWIG how to convert between a
Python object and a C++ type. You usually write two parts:

- `%typemap(in)` converts Python -> C++
- `%typemap(out)` converts C++ -> Python

## Typical Pattern (C++ struct <-> Python dict)

1) Decide how the C++ type should look in Python (for example, a dict with keys
   `x` and `y`).
2) Write `%typemap(in)` to validate the Python input and build the C++ value.
3) Write `%typemap(out)` to build a Python object from the C++ result.
4) Add error handling for bad input types.

## Example Snippets

```c
%typemap(in) Point {
    if (!PyDict_Check($input)) {
        PyErr_SetString(PyExc_TypeError, "Point must be a dict");
        SWIG_fail;
    }
    PyObject* xobj = PyDict_GetItemString($input, "x");
    PyObject* yobj = PyDict_GetItemString($input, "y");
    if (!xobj || !yobj || !PyLong_Check(xobj) || !PyLong_Check(yobj)) {
        PyErr_SetString(PyExc_TypeError, "Point dict must contain int x/y");
        SWIG_fail;
    }
    $1 = Point{static_cast<int>(PyLong_AsLong(xobj)),
               static_cast<int>(PyLong_AsLong(yobj))};
}

%typemap(out) Point {
    PyObject* dict = PyDict_New();
    PyDict_SetItemString(dict, "x", PyLong_FromLong(result.x));
    PyDict_SetItemString(dict, "y", PyLong_FromLong(result.y));
    resultobj = dict;
}
```

## Checklist

- Choose the Python representation for the C++ type.
- Validate input types in `%typemap(in)`.
- Use `PyErr_SetString` + `SWIG_fail` on invalid input.
- Build the C++ value into `$1` (or `$2`, `$3` for other parameters).
- Build the Python return object and assign it to `resultobj`.
- Think about ownership and lifetime if you allocate memory.

## What Are $1 and $resultobj?

They are SWIG typemap variables (placeholders) that SWIG replaces in the
generated wrapper code:

- `$input` is the incoming Python object.
- `$1`, `$2`, ... are the C++ function arguments you must fill.
- `$result` is the C++ return value.
- `$resultobj` is the Python object you return.

They are SWIG typemap variables. In generated wrappers, these commonly map to
local variables named `result` and `resultobj`, which you can also use directly
in typemap bodies.

## What Are PyDict_Check, PyLong_FromLong, etc.?

These are functions from the Python C API, which is the standard C interface
for building and inspecting Python objects from C/C++ code. For example:

- `PyDict_Check(obj)` checks if a Python object is a dict.
- `PyDict_GetItemString(dict, "x")` gets a dict value by key.
- `PyLong_Check(obj)` checks if a Python object is an integer.
- `PyLong_FromLong(n)` creates a Python int from a C `long`.
- `PyErr_SetString(...)` raises a Python exception.

They are standard API functions provided by Python, not SWIG keywords.

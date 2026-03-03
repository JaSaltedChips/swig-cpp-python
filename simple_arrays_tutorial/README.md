# SWIG C++ to Python Example: Arrays (Fixed Size)

This tutorial builds on the simple calculator example and shows how to accept a
fixed-size C array from Python. We map a Python list of three numbers to a C++
parameter declared as `const double values[3]`.

## Key Idea

C arrays do not carry length information at runtime. The typemap is responsible
for validating the Python input and copying values into a fixed-size C array
before the C++ function is called.

## Project Files

- `calculator.cpp`
  - C++ implementation with a new `sum3` method that takes a fixed-size array.

- `cpp_to_python.i`
  - SWIG interface file with a custom typemap for `const double[3]`.

- `setup.py`
  - Build script that compiles the wrapper and C++ source into a Python module.

- `test_arrays.py`
  - Simple test script that exercises the array binding.

## The Typemap (What It Does)

The typemap:
- Accepts any Python sequence (list or tuple).
- Checks that it has exactly 3 elements.
- Converts each element to a float.
- Copies the values into a C array.

Because C arrays are just pointers, SWIG needs explicit rules to handle them.

## Build Instructions

### 1) Generate the SWIG wrapper

```
swig -c++ -python cpp_to_python.i
```

Outputs:
- `cpp_to_python_wrap.cxx`
- `rechner_arrays.py`

### 2) Build the Python extension

```
py -3 .\setup.py build_ext --inplace
```

Outputs:
- `_rechner_arrays.pyd` (or a tagged variant like `_rechner_arrays.cp39-win_amd64.pyd`)

### 3) Run the test

```
py -3 .\test_arrays.py
```

Expected output is similar to:

```
Sum3: 7.0
Sum3 (ints): 6.0
Add: 9.0
```

## Notes

- If the list length is not 3, the typemap raises a Python `ValueError`.
- This example copies the array; no reference is kept after the call.

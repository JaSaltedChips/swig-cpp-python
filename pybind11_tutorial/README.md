# PyBind11 C++ to Python Example (Calculator)

This tutorial recreates the simple SWIG calculator example using PyBind11. You
write the bindings directly in C++ and build a native Python extension.

## Project Files

- `calculator.cpp`
  - C++ implementation plus PyBind11 bindings.

- `setup.py`
  - Build script for the Python extension using PyBind11.

- `test_math.py`
  - Simple test script that imports the module and calls its methods.

## Build Instructions

### 1) Create and activate a virtual environment

```
py -3 -m venv .venv
.\.venv\Scripts\Activate.ps1
```

### 2) Install PyBind11

```
py -3 -m pip install pybind11
```

### 3) Build the extension

```
py -3 .\setup.py build_ext --inplace
```

Outputs:
- `rechner_pybind.pyd` (or a tagged variant like `rechner_pybind.cp39-win_amd64.pyd`)

### 4) Run the test

```
py -3 .\test_math.py
```

Expected output is similar to:

```
Add: 8
Multiply: 28
Power: 1024
Square Root: 4
```

## How It Works

- `PYBIND11_MODULE(rechner_pybind, m)` defines the Python module.
- `py::class_<Calculator>` exposes the C++ class to Python.
- Each `.def(...)` binds a C++ method to a Python method of the same name.

## Quick Command Summary

```
py -3 -m venv .venv
.\.venv\Scripts\Activate.ps1
py -3 -m pip install pybind11
py -3 .\setup.py build_ext --inplace
py -3 .\test_math.py
```

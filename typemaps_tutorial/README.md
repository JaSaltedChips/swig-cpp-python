# SWIG Typemaps Tutorial: Dict <-> C++ Struct

This tutorial shows how to use SWIG typemaps to convert between a C++ struct and
Python dictionaries. Typemaps are small code snippets that tell SWIG how to
translate values as they cross the language boundary.

## Why Typemaps Matter

SWIG can map many built-in types automatically, but for custom types (like C++
structs) you must define the conversion rules. A typemap answers questions like:

- What Python types are accepted as input for a C++ parameter?
- How do you build a Python object from a C++ return value?
- Who owns the memory created during conversion?

In this example, a `Point` struct is represented in Python as a `dict` with
integer keys `x` and `y`.

## Project Files

- `point.h` / `point.cpp`
  - Defines a simple `Point` struct and a few functions that use it.

- `typemaps_demo.i`
  - SWIG interface file that contains the custom typemaps.

- `setup.py`
  - Build script for the Python extension.

- `test_typemaps.py`
  - Test script showing the Python API.

## The Typemap Itself (Key Idea)

Inside `typemaps_demo.i`, two typemaps do the work:

- `%typemap(in) Point` converts a Python `dict` into a C++ `Point`.
- `%typemap(out) Point` converts a C++ `Point` into a Python `dict`.

The `in` typemap checks types and builds a `Point` from `dict["x"]` and
`dict["y"]`. The `out` typemap builds a new Python `dict` and returns it.

## Build Instructions

### 1) Generate the SWIG wrapper

```
swig -c++ -python typemaps_demo.i
```

Outputs:
- `typemaps_demo_wrap.cxx`
- `typemaps_demo.py`

### 2) Build the Python extension

```
py -3 .\setup.py build_ext --inplace
```

Outputs:
- `_typemaps_demo.pyd` (or a tagged variant like `_typemaps_demo.cp39-win_amd64.pyd`)

### 3) Run the test

```
py -3 .\test_typemaps.py
```

Expected output is similar to:

```
make_point: {'x': 3, 'y': 7}
add_points: {'x': 1, 'y': 9}
scale_point: {'x': 6, 'y': 15}
manhattan_length: 5
```

## Notes On Ownership

The `out` typemap creates a new Python `dict` each time, so Python owns the
result. The `in` typemap does not allocate long-lived C++ memory; it builds a
stack `Point` for the call. That keeps this example safe and simple.

## Additional Notes

See [typemaps_tutorial/TYPEmaps_notes.md](typemaps_tutorial/TYPEmaps_notes.md) for a short guide and checklist on writing typemaps.

# SWIG C++ to Python Example: Difficult Types

This tutorial focuses on C++ types that are harder to expose to Python. It uses
`std::string`, `std::vector<std::string>`, and `const&` parameters so you can see
why ownership and lifetimes matter.

## Why Some C++ Types Are Hard To Expose

1) Ownership and lifetimes
   - Raw pointers and references do not tell Python who owns the memory.
   - If C++ frees an object while Python still holds a reference, you get crashes.

2) Templates and STL containers
   - `std::vector<T>` is a template; SWIG needs a concrete `T` to generate code.
   - You must provide a `%template` so Python knows how to map lists to vectors.

3) Copy vs reference semantics
   - Python expects values to keep working after return.
   - Returning a C++ reference ties the value to the C++ object's lifetime.

4) Overloads, const, and implicit conversions
   - C++ uses overloads and implicit conversions; Python does not.
   - You often need typemaps or explicit wrappers to disambiguate.

5) Exceptions and error reporting
   - C++ exceptions do not automatically become Python exceptions.
   - You usually need exception typemaps or manual translation.

6) Callbacks and virtual methods
   - Python functions passed into C++ need glue code and careful GIL handling.

This tutorial addresses 1-3 in a minimal, buildable example.

## Project Files

- `word_store.cpp`
  - C++ implementation with `std::string` and `std::vector<std::string>`.

- `word_store.i`
  - SWIG interface file. Uses STL typemaps and a `%template` for vectors.

- `setup.py`
  - Build script that compiles the wrapper and C++ source into a Python module.

- `test_words.py`
  - Simple test script that exercises the bindings.

## Build Instructions

### 1) Generate the SWIG wrapper

```
swig -c++ -python word_store.i
```

Outputs:
- `word_store_wrap.cxx`
- `wordstore.py`

### 2) Build the Python extension

```
py -3 .\setup.py build_ext --inplace
```

Outputs:
- `_wordstore.pyd` (or a tagged variant like `_wordstore.cp39-win_amd64.pyd`)

### 3) Run the test

```
py -3 .\test_words.py
```

Expected output is similar to:

```
Count: 3
Join: alpha | beta | gamma
Words (copy): ['alpha', 'beta', 'gamma']
Words (ref): ['alpha', 'beta', 'gamma']
Total length: 11
```

## What This Tutorial Demonstrates

- `std::string` maps cleanly to Python `str` via `std_string.i`.
- `std::vector<std::string>` maps to Python `list` via `std_vector.i` and
  `%template(StringVector)`.
- `words()` returns a copy (safe). `words_ref()` returns a reference (fast but
  tied to `WordStore`'s lifetime).

## Lifetime Caveat (Why References Are Tricky)

`words_ref()` returns a reference to internal storage. In Python you must keep
`WordStore` alive while using that list. If the C++ object is destroyed, the
reference becomes invalid. In real projects, you often avoid exposing raw
references and return copies or smart pointers instead.

## Quick Command Summary

```
# 1) Generate wrappers
swig -c++ -python word_store.i

# 2) Build extension
py -3 .\setup.py build_ext --inplace

# 3) Run test
py -3 .\test_words.py
```

Note: SWIG handles ownership when converting C++ returns to Python. A copy return creates new C++ storage that Python owns; a reference return exposes existing C++ storage owned by the original object, so its lifetime must outlive Python's use.

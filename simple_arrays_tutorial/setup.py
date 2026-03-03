from distutils.core import Extension, setup
import os
import sysconfig

MODULE_NAME = "rechner_arrays"
CPP_FILE = "calculator.cpp"
INTERFACE_FILE = "cpp_to_python.i"

python_include = sysconfig.get_path("include")
python_lib = sysconfig.get_config_var("LIBDIR") or sysconfig.get_config_var("LIBPL")

interface_base = os.path.splitext(INTERFACE_FILE)[0]
wrapper_file = f"{interface_base}_wrap.cxx"

ext_modules = [
    Extension(
        f"_{MODULE_NAME}",
        sources=[wrapper_file, CPP_FILE],
        language="c++",
        include_dirs=[python_include],
        library_dirs=[python_lib] if python_lib else [],
    )
]

setup(
    name=MODULE_NAME,
    version="1.0",
    ext_modules=ext_modules,
)

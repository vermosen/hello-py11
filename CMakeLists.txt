cmake_minimum_required(VERSION 3.15...3.19)

project(habu VERSION "0.0.1")

if(SKBUILD)
  # figure out where the pybind11 headers are located
  execute_process(
    COMMAND
      "${PYTHON_EXECUTABLE}" -c
      "import pybind11; print(pybind11.get_cmake_dir())"
    OUTPUT_VARIABLE _PYBIND11_HEADER_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ECHO STDOUT
  )

  # numpy headers
  execute_process(
    COMMAND "${PYTHON_EXECUTABLE}" -c
            "import numpy; print(numpy.get_include())"
    OUTPUT_VARIABLE _NUMPY_HEADER_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ECHO STDOUT
  )


  list(APPEND CMAKE_PREFIX_PATH "${_PYBIND11_HEADER_DIR}" "${_NUMPY_HEADER_DIR}")
endif()

# find pybind11
find_package(pybind11 CONFIG REQUIRED)

# c++ include
include_directories(src)

# add c++ sources
add_subdirectory(src)
add_subdirectory(python)

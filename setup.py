# -*- coding: utf-8 -*-

from __future__ import print_function

import sys

try:
    from skbuild import setup
except ImportError:
    print(
        "Please update pip, you need pip 10 or greater,\n"
        " or you need to install the PEP 518 requirements in pyproject.toml yourself",
        file=sys.stderr,
    )
    raise

from setuptools import find_packages 


setup(
    name="habu",
    version="0.0.1",
    description="a minimal example package (with pybind11) to test numpy bindings",
    author="Jean-Mathieu Vermosen",
    license="MIT",
    packages=find_packages(where = 'python'),
    package_dir={"": "python"},
    cmake_install_dir="python/habu",
    cmake_args=[],
    include_package_data = True,
    extras_require={"test": ["pytest"]},
)

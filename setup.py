# from setuptools import setup
import os
import re
from pathlib import Path

from skbuild import setup

for i in (Path(__file__).resolve().parent / "_skbuild").rglob("CMakeCache.txt"):
    i.write_text(re.sub("^//.*$\n^[^#].*pip-build-env.*$", "", i.read_text(), flags=re.M))

print("###### show all environment variables and their values. ######")
print(os.environ)

#  python -c 'import site; print(site.getsitepackages())'

setup(
    name="nest_wheel",
    version="0.1.4",
    author="steffengraber",
    author_email="s.graber@fz-juelich.de",
    description="A test for nest",
    url="https://github.com/steffengraber/nest-simulator.git",
    download_url="https://github.com/steffengraber/nest-simulator/archive/refs/heads/nest-wheel.zip",
    packages=["nest"],
    python_requires=">=3.8, <4",
    install_requires=[
        "libtool",
        "boost",
        "numpy",
        "pandas",
        "scipy",
        "matplotlib",
        "mpi4py",
        "h5py",
        "black",
        "pre-commit",
        "isort",
        "notebook",
        "jupyterlab",
        "csa",
        "pydot",
        # TESTING
        "pytest",
        "pytest-timeout",
        "pytest-xdist",
        "pytest-pylint",
        "pytest-mypy",
        "pytest-cov",
        "data-science-types",
        "terminaltables",
        "pycodestyle",
        "pydocstyle",
        "rstcheck",
        "mypy >= 0.8",
        "junitparser >= 2",
        "clang-format == 17.0.4",
        "attrs",
    ],
    cmake_install_dir=".",
    cmake_args=[
        "-Dwith-python=ON",
        "-Dwith-boost=ON",
        "-Dwith-gsl=ON",
        "-Dwith-readline=ON",
        "-Dwith-ltdl=ON",
        "-Dwith-openmp=ON",
    ],
)
# - Could NOT find Readline (missing: READLINE_LIBRARY NCURSES_LIBRARY READLINE_INCLUDE_DIR)
# -- Could NOT find PkgConfig (missing: PKG_CONFIG_EXECUTABLE)
# -- Could NOT find GSL (missing: GSL_INCLUDE_DIR GSL_LIBRARY GSL_CBLAS_LIBRARY) (found version "")
# -- Could NOT find Boost (missing: Boost_INCLUDE_DIR) (Required is at least version "1.69.0")

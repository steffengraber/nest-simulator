# from setuptools import setup
from skbuild import setup
import re
from pathlib import Path

for i in (Path(__file__).resolve().parent / "_skbuild").rglob("CMakeCache.txt"):
    i.write_text(re.sub("^//.*$\n^[^#].*pip-build-env.*$", "", i.read_text(), flags=re.M))

setup(
    name='nest_wheel',
    version='0.1.2set',
    author="steffengraber",
    author_email="s.graber@fz-juelich.de",
    description="A test for nest",
    url="https://github.com/steffengraber/nest-simulator.git",
    download_url="https://github.com/steffengraber/nest-simulator/archive/refs/heads/nest-wheel.zip",
    packages=['nest'],
    python_requires=">=3.8, <4",
    install_requires=[
            'libtool',
            'pytest',
            'pytest-timeout',
            'pytest-xdist',
            'numpy',
            'pandas',
            'scipy',
            'mpi4py',
            'terminaltables',
            'pycodestyle'
      ],
    cmake_install_dir='.'
    )

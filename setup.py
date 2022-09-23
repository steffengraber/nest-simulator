# from setuptools import setup
from skbuild import setup  # This line replaces 'from setuptools import setup'

setup(
    name='nest-wheel-test',
    version='0.1.2',
    author="steffengraber",
    author_email="s.graber@fz-juelich.de",
    description="A test for nest",
    url="https://github.com/steffengraber/nest-simulator.git",
    download_url="https://github.com/steffengraber/nest-simulator/archive/refs/heads/nest-wheel.zip",
    packages=['nest'],
    python_requires=">=3.8",
    cmake_install_dir='.'
    )

#from setuptools import setup
from skbuild import setup  # This line replaces 'from setuptools import setup'
import pathlib


here = pathlib.Path(__file__).parent.resolve()

# Get the long description from the README file
long_description = (here / "README.md").read_text(encoding="utf-8")


setup(
    name = 'nest-wheel-test',
    version='0.1.1',
    author="steffengraber",
    author_email="s.graber@fz-juelich.de",
    description="A test for nest",
    long_description=long_description,
    url="github source url",
    download_url="download link",
    packages=['nest'],
    python_requires=">=3.8",
    cmake_install_dir='.',
)
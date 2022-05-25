#!/bin/sh

# Make PyNEST available by prepending its path to PYTHONPATH in a safe way.
export PYTHONPATH="/home/graber/work/nest-simulator/_skbuild/linux-x86_64-3.8/cmake-install/lib/python3.8/site-packages${PYTHONPATH:+:$PYTHONPATH}"

# Make NEST executables available by prepending their path to PATH.
export PATH="/home/graber/work/nest-simulator/_skbuild/linux-x86_64-3.8/cmake-install/bin:${PATH}"

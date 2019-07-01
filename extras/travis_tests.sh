#!/bin/bash

# travis_build.sh
#
# This file is part of NEST.
#
# Copyright (C) 2004 The NEST Initiative
#
# NEST is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# NEST is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with NEST.  If not, see <http://www.gnu.org/licenses/>.


# This shell script is part of the NEST Travis CI build and test environment.
# It is invoked by the top-level Travis script '.travis.yml'.
#
# NOTE: This shell script is tightly coupled to Python script
#       'extras/parse_travis_log.py'.
#       Any changes to message numbers (MSGBLDnnnn) or the variable name
#      'file_names' have effects on the build/test-log parsing process.


# Exit shell if any subcommand or pipline returns a non-zero status.
set -e

#mkdir -p $HOME/.matplotlib
#cat > $HOME/.matplotlib/matplotlibrc <<EOF
#    backend : svg
#EOF

if [ "$xMPI" = "1" ] ; then
    CONFIGURE_MPI="-Dwith-mpi=ON"
    echo "MPI ON"
else
    CONFIGURE_MPI="-Dwith-mpi=OFF"
    echo "MPI OFF or not set"
fi
NEST_VPATH=$HOME/build
NEST_RESULT=$HOME/result
if [ "$(uname -s)" = 'Linux' ]; then
    NEST_RESULT=$(readlink -f $NEST_RESULT)
else
    NEST_RESULT=$(greadlink -f $NEST_RESULT)
fi

echo $NEST_VPATH
mkdir -p "$NEST_VPATH" "$NEST_RESULT"
mkdir -p "$NEST_VPATH/reports"


cd "$NEST_VPATH"

# cp ../examples/sli/nestrc.sli ~/.nestrc
# Explicitly allow MPI oversubscription. This is required by Open MPI versions > 3.0.
# Not having this in place leads to a "not enough slots available" error.
if [[ "$OSTYPE" == "darwin"* ]] ; then
    sed -i -e 's/mpirun -np/mpirun --oversubscribe -np/g' ~/.nestrc
fi

echo
echo "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +"
echo "+               C O N F I G U R E   N E S T   B U I L D                       +"
echo "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +"


cmake -DCMAKE_INSTALL_PREFIX="${NEST_RESULT}" \
        -Dwith-optimize=ON \
        -Dwith-warning=ON \
        -Dwith-boost=ON \
        -Dwith-python=3 \
        ${CONFIGURE_MPI} \
        /home/nest/data && \
make  && \
make install && \
make installcheck
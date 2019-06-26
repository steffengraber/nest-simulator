FROM buildpack-deps:bionic as builderslim216
MAINTAINER "Steffen Graber" <s.graber@fz-juelich.de>

ENV TERM=xterm \
    TZ=Europe/Berlin \
    DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    cmake \
    cython3 \
    jq \
    libboost-filesystem-dev \
    libboost-regex-dev \
    libboost-wave-dev \
    libboost-python-dev \
    libboost-program-options-dev \
    libboost-test-dev \
    libgsl-dev \
    libltdl7 \
    libltdl-dev \
    libmusic1v5 \
    libmusic-dev \
    libncurses5-dev \
    libopenmpi-dev \
    libpcre3 \
    libpcre3-dev \
    llvm-3.9-dev \
    music-bin \
    openmpi-bin \
    pep8 \
    python3.6-dev \
    python3-ipython \
    python3-jupyter-core \
    python3-matplotlib \
    python3-mpi4py \
    python3-nose \
    python3-numpy \
    python3-pandas \
    python3-path \
    python3-scipy \
    python3-setuptools \
    python3-statsmodels \
    python-dev \
    vera++ \
    wget  && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/nest/nest-simulator/archive/master.tar.gz && \
  mkdir nest-build && \
  tar zxf nest-simulator-master.tar.gz && \
  cd  nest-build && \
  cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/nest/ \
        -Dwith-python=3 \
        ../nest-simulator-master && \
  make && \
  make install && \
  make installcheck
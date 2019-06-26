FROM steffengraber/travis-nest:latest as builder216
MAINTAINER "Steffen Graber" <s.graber@fz-juelich.de>

ENV TERM=xterm \
    TZ=Europe/Berlin \
    DEBIAN_FRONTEND=noninteractive

RUN wget https://github.com/nest/nest-simulator/archive/master.tar.gz && \
  mkdir nest-build && \
  tar zxf master.tar.gz && \
  cd  nest-build && \
  cmake -DCMAKE_INSTALL_PREFIX:PATH=/opt/nest/ \
        -Dwith-python=3 \
        ../nest-simulator-master && \
  make && \
  make install && \
  make installcheck
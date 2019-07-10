# prepare base image
FROM debian:stretch-slim
RUN apt-get update && \
    apt-get install -y build-essential gcc cmake make unzip wget apt-utils

# setup env
RUN mkdir /aip
WORKDIR /aip

# install pytorch
RUN wget https://download.pytorch.org/libtorch/nightly/cpu/libtorch-shared-with-deps-latest.zip
RUN unzip libtorch-shared-with-deps-latest.zip -d /aip

# install zeromq libraries
RUN echo "deb http://download.opensuse.org/repositories/network:/messaging:/zeromq:/release-stable/Debian_9.0/ ./" >> /etc/apt/sources.list
RUN wget https://download.opensuse.org/repositories/network:/messaging:/zeromq:/release-stable/Debian_9.0/Release.key -O- | apt-key add
RUN apt-get install -y libzmq3-dev

# install zeromq cpp wrapper
RUN wget https://github.com/zeromq/cppzmq/archive/master.zip
RUN unzip master.zip && rm master.zip && mv cppzmq-master /aip/cppzmq
RUN cd /aip/cppzmq && mkdir build && cd build && cmake .. && make -j4 install

# copy sources
ADD ./src/ /aip/src
ADD CMakeLists.txt /aip/CMakeLists.txt
ADD docker-compile.sh /aip/compile.sh

# compile server
RUN /aip/compile.sh

# clean-up to reduce image size
RUN chmod 777 /aip/build/aip-server && mv /aip/build/aip-server /aip/aip-server
RUN rm -rf /aip/src && \
    rm -rf /aip/build && \
    rm -rf /aip/libtorch/include && \
    rm -rf /aip/libtorch/share && \
    apt-get purge -y build-essential gcc cmake make unzip wget apt-utils && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

ENTRYPOINT ["/aip/aip-server"]

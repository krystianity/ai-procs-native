# prepare base image
FROM debian:stretch-slim
RUN apt-get update && \
    apt-get install -y build-essential gcc cmake make

# setup env
RUN mkdir /aip
WORKDIR /aip
ADD ./src/ /aip/src
ADD CMakeLists.txt /aip/CMakeLists.txt
ADD docker-compile.sh /aip/compile.sh

# move libraries
ADD ./libtorch/ /aip/libtorch

# compile server
RUN /aip/compile.sh

# clean-up to reduce image size
RUN chmod 777 /aip/build/aip-server && mv /aip/build/aip-server /aip/aip-server
RUN rm -rf /aip/src && \
    rm -rf /aip/build && \
    rm -rf /aip/libtorch/include && \
    rm -rf /aip/libtorch/share && \
    apt-get purge -y build-essential gcc cmake make && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

ENTRYPOINT ["/aip/aip-server"]

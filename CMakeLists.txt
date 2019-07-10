cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(ai-procs-native)

find_package(Torch REQUIRED)
find_package(cppzmq)

add_executable(aip-server src/aip_server.cpp)
target_link_libraries(aip-server "${TORCH_LIBRARIES}" cppzmq)
target_link_libraries(aip-server cppzmq)
set_property(TARGET aip-server PROPERTY CXX_STANDARD 11)
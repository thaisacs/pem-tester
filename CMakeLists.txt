cmake_minimum_required(VERSION 2.6)
project(pem)

set(CMAKE_CXX_FLAGS "-O3")

include_directories(includes)

file(GLOB FONTES "sources/*.cpp")

add_executable(pemtester ${FONTES})

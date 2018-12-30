cmake_minimum_required(VERSION 2.6)
project(pem-tester)

include_directories(includes)

file(GLOB FONTES "sources/*.cpp")

add_executable(pemtester ${FONTES})

install(TARGETS pemtester RUNTIME DESTINATION bin)

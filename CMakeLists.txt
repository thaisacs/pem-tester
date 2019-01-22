cmake_minimum_required(VERSION 2.6)
project(pem)

set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_COMPILER "g++-7")

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

include_directories(includes)

file(GLOB FONTES "sources/*.cpp")

add_executable(pemtester ${FONTES})

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(pemtester ${llvm_libs})

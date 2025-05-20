cmake_minimum_required(VERSION 3.13)

project(LoopUnrollPass)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard to conform to")
set(CMAKE_CXX_STANDARD_REQUIRED YES)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader analysis transformutils)

add_library(LoopUnrollPass MODULE LoopUnroll.cpp)

target_link_libraries(LoopUnrollPass PRIVATE ${llvm_libs})

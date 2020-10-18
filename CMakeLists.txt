set(CMAKE_CXX_COMPILER "/usr/local/Cellar/llvm/10.0.1_1/bin/clang++")

cmake_minimum_required(VERSION 3.1)

project(Skeleton)

# support C++14 features used by LLVM 10.0.0
set(CMAKE_CXX_STANDARD 14)

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(skeleton)  # Use your pass name here.
add_subdirectory(examples)  # Use your pass name here.

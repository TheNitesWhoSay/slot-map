# Compile the slot map example executable and unit tests
cmake_minimum_required(VERSION 3.20)

set(This SlotMap)

project(${This})

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(/permissive- ${ASAN})

enable_testing()

add_subdirectory(src) # Compiles the slot map example executable
add_subdirectory(test) # Compiles the slot map test executable
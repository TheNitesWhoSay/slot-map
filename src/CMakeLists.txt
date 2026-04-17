# Compile the slot map executable
cmake_minimum_required (VERSION 3.20)

set(This SlotMapExample)

project(${This})

#include_directories()

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(/permissive- ${ASAN})

set(ExamplePath ${CMAKE_CURRENT_SOURCE_DIR})
cmake_path(GET ExamplePath PARENT_PATH SlotMapRootPath)
include_directories(${SlotMapRootPath}/include)

set(Headers
  
)
set(Sources
  main.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${This} ${Sources} ${Headers})

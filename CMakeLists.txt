# Compile the slot map example executable and unit tests
cmake_minimum_required(VERSION 3.20)

set(This SlotMap)

project(${This})

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

if ( PROJECT_IS_TOP_LEVEL )
  set(SLOTMAP_BUILD_EXAMPLES TRUE)
  set(SLOTMAP_BUILD_TESTS TRUE)
else()
  add_library(${PROJECT_NAME} INTERFACE)
  target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

if ( SLOTMAP_BUILD_EXAMPLES )
  add_subdirectory(src) # Compiles the slot map example executable
endif()

if ( SLOTMAP_BUILD_TESTS )
  enable_testing()
  add_subdirectory(test) # Compiles the slot map test executable
endif()

# Compile the test executable
cmake_minimum_required (VERSION 3.20)

set(This SlotMapTest)

project(${This})

set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(/permissive- ${ASAN})

set(TestPath ${CMAKE_CURRENT_SOURCE_DIR})
cmake_path(GET TestPath PARENT_PATH SlotMapRootPath)
include_directories(${SlotMapRootPath}/include)

set(Headers
  
)
set(Sources
  slot_map_test.cpp
  test_main.cpp
)

add_executable(${This} ${Sources} ${Headers})

enable_testing()

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

target_link_libraries(${This} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

if ( WIN64_DEBUG_ASAN ) # The asan dll must be made available for gtest_discover_tests to use the test exe
    configure_file("$ENV{VCToolsInstallDir}/bin/Hostx64/x64/clang_rt.asan_dynamic-x86_64.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/clang_rt.asan_dynamic-x86_64.dll" COPYONLY)
endif ()

gtest_discover_tests(${This} DISCOVERY_MODE PRE_TEST)

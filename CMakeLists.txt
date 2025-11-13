cmake_minimum_required(VERSION 3.14)
project(XCanvas)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CODE_DIR ${CMAKE_SOURCE_DIR}/Code)

include(FetchContent)
include(CMake/FetchDeps.cmake)

add_subdirectory(${CODE_DIR}/XCanvas)

# Testbed application
add_subdirectory(${CMAKE_SOURCE_DIR}/Testbed)
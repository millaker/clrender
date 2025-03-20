cmake_minimum_required(VERSION 3.28)
project(clrender)

# generate compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++17
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0")

# Default to debug build
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# set build dir
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(third_party)
add_subdirectory(src)

message(STATUS "clrender will be built with ${CMAKE_BUILD_TYPE} mode")

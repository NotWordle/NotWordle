cmake_minimum_required(VERSION 3.10)

# set project name and version
project(NotWordle VERSION 0.1)
add_subdirectory(src)

# set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(src/Version.h.in Version.h)

message(${CMAKE_SOURCE_DIR})

set(HEADERS
  "${CMAKE_SOURCE_DIR}/inc")

set(SOURCES
  src/main.cpp)

add_executable(NotWordle ${SOURCES})
target_include_directories(NotWordle PRIVATE "${HEADERS}")

target_include_directories(NotWordle PUBLIC "${PROJECT_BINARY_DIR}")

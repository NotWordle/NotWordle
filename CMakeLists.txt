cmake_minimum_required(VERSION 3.10)

# set project name and version
project(NotWordle VERSION 0.5)

# set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# sets up cmake macro to use versioning in source code
configure_file(src/Version.h.in Version.h)

add_subdirectory(lib/googletest)


set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/inc")

set(HEADERS
  inc/game/Game.h
  inc/game/Dictionary.h
  inc/game/Validity.h
  inc/game/Color.h
  inc/game/objects/GameObject.h
  inc/game/objects/Grid.h
  inc/game/objects/Space.h
)

set(SOURCES
  src/game/Game.cpp
  src/game/Dictionary.cpp
  src/game/objects/Grid.cpp
  src/game/objects/Space.cpp
)

add_library(wordlegame
  ${SOURCES}
  ${HEADERS}
)

# create executable in build/bin
add_executable(NotWordle src/main.cpp)
set_target_properties(NotWordle
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

include_directories(${INCLUDE_DIR})
target_include_directories(NotWordle PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(NotWordle wordlegame)

# Unit Tests

enable_testing()

SET( GTEST_LIBRARIES gtest gtest_main gmock gmock_main )
SET( CMAKE_BUILD_TYPE Debug )


include(cmake/CodeCoverage.cmake)
SET(CMAKE_CXX_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")

add_subdirectory(test)

# Documentation using Doxygen
include(cmake/Doxygen.cmake)
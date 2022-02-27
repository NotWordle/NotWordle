cmake_minimum_required(VERSION 3.10)

# set project name and version
project(NotWordle VERSION 0.5)

# set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(BUILD_WITH_CPPLINT)
  message("BUILD_WITH_CPPLINT is ON, all .cpp and .h files will be linted with cpplint for conformity")
else(BUILD_WITH_CPPLINT)
  message("BUILD_WITH_CPPLINT is OFF, run cmake with \"-DBUILD_WITH_CPPLINT=ON\" to enable it")
endif(BUILD_WITH_CPPLINT)

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
include(cmake/CodeCoverage.cmake)
add_subdirectory(test)

# Documentation using Doxygen
include(cmake/Doxygen.cmake)

# Linting

# adding this custom will have cmake run cpplint over the source code and header
# files after it's been compiled and linked
if(BUILD_WITH_CPPLINT)
  add_custom_command(
    TARGET NotWordle
    POST_BUILD
    DEPENDS ${SOURCES} ${HEADERS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND cpplint
    ARGS --quiet --repository=${CMAKE_SOURCE_DIR} --recursive --linelength=120 --filter=-legal/copyright ${SOURCES} ${HEADERS}
    COMMENT "Linting main source/header files with cpplint"
  )
endif(BUILD_WITH_CPPLINT)
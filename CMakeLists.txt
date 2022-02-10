cmake_minimum_required(VERSION 3.10)

# set project name and version
project(NotWordle VERSION 0.3)
add_subdirectory(src)

# set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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

add_executable(NotWordle  src/main.cpp ${SOURCES} ${HEADERS})
target_include_directories(NotWordle PRIVATE "${INCLUDE_DIR}")
target_include_directories(NotWordle PUBLIC "${PROJECT_BINARY_DIR}")

enable_testing()

# test files

set(TEST_SOURCE
  test/game/objects/SpaceTest.cpp
)

add_executable(NotWordleUT ${TEST_SOURCE} ${HEADERS} ${SOURCES})
target_include_directories(NotWordleUT PRIVATE "${INCLUDE_DIR}")
target_include_directories(NotWordleUT PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(NotWordleUT gtest_main)


include(GoogleTest)
gtest_discover_tests(NotWordleUT)

include(GoogleTest)

set(UT_BIN_NAME NotWordleUT)


set(TEST_SOURCE
  game/objects/SpaceTest.cpp
  game/objects/GridTest.cpp
  game/GameTest.cpp
  game/ValidityTest.cpp
  game/ColorTest.cpp
  game/DictionaryTest.cpp
)

# copy over expected output files to build folder for ease-of-use
file(COPY expected/ DESTINATION expected/)

# create separate executable to for running unit tests
add_executable(${UT_BIN_NAME} ${TEST_SOURCE})
target_link_libraries(${UT_BIN_NAME} wordlegame)
target_link_libraries(${UT_BIN_NAME} ${GTEST_LIBRARIES})

target_include_directories(${UT_BIN_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

gtest_discover_tests(${UT_BIN_NAME})

# this target creates the xml file that can be uploaded to cobertura for parsing
SETUP_TARGET_FOR_COVERAGE_COBERTURA(
  coverage_${UT_BIN_NAME}
  ${UT_BIN_NAME}
  coverage_${UT_BIN_NAME}_dir
)

# this target will allow us to examine basic code coverage locally
SETUP_TARGET_FOR_COVERAGE(
  coverage_${UT_BIN_NAME}_local
  ${UT_BIN_NAME}
  coverage_${UT_BIN_NAME}_dir
)

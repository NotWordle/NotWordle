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

# Linting

# adding this custom will have cmake run cpplint over the test source code after
# it's been compiled and linked
if(BUILD_WITH_CPPLINT)
  add_custom_command(
    TARGET NotWordleUT
    POST_BUILD
    DEPENDS ${TEST_SOURCE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND cpplint
    ARGS --quiet --repository=${CMAKE_SOURCE_DIR} --recursive --linelength=120 --filter=-legal/copyright ${TEST_SOURCE}
    COMMENT "Linting test source files with cpplint"
  )
endif(BUILD_WITH_CPPLINT)

include(GoogleTest)

set(UT_BIN_NAME NotWordleUT)


set(TEST_SOURCE
  game/objects/SpaceTest.cpp
  game/ValidityTest.cpp
  game/ColorTest.cpp
  game/DictionaryTest.cpp
)

add_executable(${UT_BIN_NAME} ${TEST_SOURCE})
target_link_libraries(${UT_BIN_NAME} wordlegame)
target_link_libraries(${UT_BIN_NAME} ${GTEST_LIBRARIES})

target_include_directories(${UT_BIN_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

gtest_discover_tests(${UT_BIN_NAME})

SETUP_TARGET_FOR_COVERAGE_COBERTURA(
  coverage_${UT_BIN_NAME}
  ${UT_BIN_NAME}
  coverage_${UT_BIN_NAME}_dir
)

set(SRC_FILES ${PROJECT_SOURCE_DIR}/src/glorot.cpp)
add_executable(test_glorot glorot_tests.cpp ${SRC_FILES})
include_directories(include)

#target_link_libraries(test_glorot DateConverter_lib)

target_link_libraries(test_glorot gtest gtest_main)
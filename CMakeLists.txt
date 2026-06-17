cmake_minimum_required(VERSION 4.2)

set(PROJECT_NAME test_glorot_test_example)
project(${PROJECT_NAME} CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(DisplayVars)
include(fetch3Libs)

display_vars()
fetch3Libs()

# adding sanitizer may help finding memory bugs
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
    message(STATUS "adding sanitizer")
endif()


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# dependencies
find_package(Eigen3 REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)


#include(GoogleTest)

include_directories(include)
set(SRC_FILES ${PROJECT_SOURCE_DIR}/src/glorot.cpp)
#set(TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/test_find_middle.cpp
#                   ${PROJECT_SOURCE_DIR}/tests/test_my_functions.cpp
#)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${PROJECT_SOURCE_DIR}/src/main.cpp)


# include PTHREAD
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads
        fmt::fmt
        spdlog::spdlog

)

# include Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
#find_package(Boost REQUIRED COMPONENTS system)
#if (Boost_FOUND)
#    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
#    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
#endif (Boost_FOUND)
#set(USED_BOOST_LIBS ${Boost_SYSTEM_LIBRARY})
#target_link_libraries(${PROJECT_NAME} ${USED_BOOST_LIBS})


## Locate GTest
add_subdirectory(tests)
#
#find_package(GTest REQUIRED)
#add_executable(Google_Tests_run ${TEST_SRC_FILES})
#target_link_libraries(Google_Tests_run gtest gtest_main)
#gtest_discover_tests(${PROJECT_NAME})

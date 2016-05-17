cmake_minimum_required(VERSION 2.4)

project(trax CXX)

set(BINARY_NAME trax)

set(OUT_DIR out)
set(SRC_DIR src)

set(CMAKE_CXX_FLAGS_RELEASE "-std=c++14 -Wall -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++14 -g3")
set(CMAKE_BUILD_TYPE Release)

set(PROJECT_BINARY_DIR ${OUT_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

###########################################################

file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

foreach(path IN LISTS SOURCES)
    message("source file found: ${path}")
endforeach()

add_executable(${BINARY_NAME} ${SOURCES})

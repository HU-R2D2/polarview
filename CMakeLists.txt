cmake_minimum_required(VERSION 2.8.9)
project(polarview)
find_package (Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

file(GLOB SOURCES "source/include/*.hpp")
file(GLOB SOURCES_GTEST "../adt/source/include/*.hpp" "../adt/source/src/*.cpp" "source/src/*.cpp" "source/include/*.hpp" "test/*.cpp" "test/*.hpp")

include_directories(
  ../deps/gtest-1.7.0/include
  ../deps/gtest-1.7.0)

link_directories(../deps/gtest-1.7.0/src)
ADD_LIBRARY(gtest ../deps/gtest-1.7.0/src/gtest-all.cc)
ADD_LIBRARY(gtest_main ../deps/gtest-1.7.0/src/gtest_main.cc)

add_executable(distancereading_test ${GTEST} ${SOURCES_GTEST})
target_link_libraries(distancereading_test gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
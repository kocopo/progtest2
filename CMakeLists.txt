cmake_minimum_required(VERSION 3.8)
project(progtest2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp median.cpp)
add_executable(progtest2 ${SOURCE_FILES})
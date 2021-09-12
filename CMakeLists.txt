cmake_minimum_required(VERSION 3.17)
project(ssarray)

set(CMAKE_CXX_STANDARD 17)

add_executable(ssarray ssarray_test.cpp ssarray.h doctest.h)
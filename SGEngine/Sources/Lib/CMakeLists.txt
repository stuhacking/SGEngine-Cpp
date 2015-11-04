# SGECoreLib - Low level utilities
# Most of SGECoreLib is header only with a small portion
# of complex procedures provided in a static library.
cmake_minimum_required(VERSION 2.8.11)
project(SGECoreLib)

file(GLOB_RECURSE SOURCES *.cpp .)
add_library(SGECoreLib ${SOURCES})

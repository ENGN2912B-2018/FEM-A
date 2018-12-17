cmake_minimum_required(VERSION 2.8)

project(pdeLibrary)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(diffusion ConvectionDiffusion.h ConvectionDiffusion.cpp)
add_library(blackScholes BlackScholes.h BlackScholes.cpp)

set_target_properties(diffusion PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(blackScholes PROPERTIES LINKER_LANGUAGE CXX)
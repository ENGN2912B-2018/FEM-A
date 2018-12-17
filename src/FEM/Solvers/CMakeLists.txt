cmake_minimum_required(VERSION 2.8)

project(solverLibrary)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(femBase ConvectionDiffusionFEMBase.h ConvectionDiffusionFEMBase.cpp)
add_library(eulerExplicit ConvectionDiffusionEulerExplicit.h ConvectionDiffusionEulerExplicit.cpp)

set_target_properties(femBase PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(eulerExplicit PROPERTIES LINKER_LANGUAGE CXX)
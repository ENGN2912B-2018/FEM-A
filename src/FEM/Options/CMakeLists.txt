cmake_minimum_required(VERSION 2.8)

project(optionLibrary)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(payoff Payoff.h Payoff.cpp)
add_library(americanPayoff AmericanPayoff.h AmericanPayoff.cpp)
add_library(asianPayoff AsianPayoff.h AsianPayoff.cpp)
add_library(europeanPayoff EuropeanPayoff.h EuropeanPayoff.cpp)
add_library(powerPayoff PowerPayoff.h PowerPayoff.cpp)
add_library(option Option.h Option.cpp)

set_target_properties(payoff PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(americanPayoff PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(asianPayoff PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(europeanPayoff PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(powerPayoff PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(option PROPERTIES LINKER_LANGUAGE CXX)
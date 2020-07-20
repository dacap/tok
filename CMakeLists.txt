# Tok Library
# Copyright (c) 2020 David Capello

cmake_minimum_required(VERSION 3.16)

project(tok)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TOK_BENCHMARKS "Compile tok benchmarks" OFF)

add_executable(test test.cpp)

if(TOK_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()

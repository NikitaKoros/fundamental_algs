cmake_minimum_required(VERSION 3.28)
project(fundamental_alg_cpp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Werror -pedantic -Wconversion")

add_executable(task2 task2.cpp util_task2.cpp)

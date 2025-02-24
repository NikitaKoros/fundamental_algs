cmake_minimum_required(VERSION 3.28)
project(fundamental_alg C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER "/usr/bin/gcc")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_DEBUG "-g")


add_executable(task9 task9.c util_task9.c)
target_link_libraries(task9 m)
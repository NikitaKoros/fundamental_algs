cmake_minimum_required(VERSION 3.28)
project(fundamental_alg C)

set(CMAKE_C_STANDARD 18)
set(CMAKE_C_STANDART_REQUIRED ON)
set(CMAKE_C_COMPILER "/usr/bin/gcc")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic -Wconversion")
   
add_executable(task1 task1.c util_task1.c hash_table.c)

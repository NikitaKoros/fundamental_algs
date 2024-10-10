cmake_minimum_required(VERSION 3.28)
project(fundamental_alg C)

set(CMAKE_C_STANDARD 11)

add_executable(task3 task3.c handlers.c util_task3.c)
target_link_libraries(task3 m)
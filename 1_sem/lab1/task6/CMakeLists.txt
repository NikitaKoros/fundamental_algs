cmake_minimum_required(VERSION 3.28)
project(fundamental_alg C)

set(CMAKE_C_STANDARD 11)

add_executable(task6 task6.c util_task6.c integrals.c)
target_link_libraries(task6 m)

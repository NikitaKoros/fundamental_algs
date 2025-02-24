cmake_minimum_required(VERSION 3.28)
project(fundamental_alg C)

#set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER gcc)

add_executable(task5 task5.c util_task5.c)
target_link_libraries(task5 m)
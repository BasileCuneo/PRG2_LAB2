cmake_minimum_required(VERSION 3.17)
project(lab_2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wconversion -Wsign-conversion -pedantic -Wno-pedantic-ms-format")

add_executable(lab_2 main.c boat.c)

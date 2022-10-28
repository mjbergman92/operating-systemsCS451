cmake_minimum_required(VERSION 3.23)
project(cs451projs C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(cs451projs
        a1.c
        process.c
        process.h
        queue.c
        queue.h)

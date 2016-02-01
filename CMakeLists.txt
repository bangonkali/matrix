cmake_minimum_required(VERSION 3.3)
project(MatrixOperations)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -lrt -lm")

add_subdirectory (src)
add_subdirectory (demo_src)




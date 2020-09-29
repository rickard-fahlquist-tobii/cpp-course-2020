cmake_minimum_required(VERSION 3.14)
project(homework1)

set(CMAKE_CXX_STANDARD 17)

add_executable(homework1 main.cpp)
target_compile_options(homework1
                       PUBLIC -g -Wall -O3
                        )

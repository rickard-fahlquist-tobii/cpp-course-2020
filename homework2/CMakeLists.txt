cmake_minimum_required(VERSION 3.10)
project(homework2)

set(CMAKE_CXX_STANDARD 17)

add_executable(homework2 main.cpp)

target_include_directories(homework2
                            PUBLIC ./
                            )
target_compile_options(homework2
                       PUBLIC -g -Wall
                        )

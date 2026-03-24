cmake_minimum_required(VERSION 4.1)
project(ASCII_art_maker)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(ASCII_art_maker
        src/main.cpp)

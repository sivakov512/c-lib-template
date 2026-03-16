cmake_minimum_required(VERSION 3.16)

project(tbd C)

add_library(tbd STATIC
    src/tbd.c
)
target_include_directories(tbd PUBLIC include)

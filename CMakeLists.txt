cmake_minimum_required(VERSION 3.30)
project(CVector C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS NO) # Ensure strict compliance (no GNU extensions)
add_compile_options(-std=c89 -Wall -Wextra -Wpedantic)

add_executable(untitled main.c)

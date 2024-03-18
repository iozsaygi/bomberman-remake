cmake_minimum_required(VERSION 3.27)
project(bomberman_remake C)

set(CMAKE_C_STANDARD 23)

# Add 'include' folder as header directory.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(bomberman_remake src/main.c
        src/debugger.c)
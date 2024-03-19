cmake_minimum_required(VERSION 3.27)
project(bomberman_remake C)

set(CMAKE_C_STANDARD 23)

# Set the download URL for SDL library. Using specific version for MSVC.
# Will need to target different version for other compilers and platforms.
set(SDL2_DOWNLOAD_URL "https://github.com/libsdl-org/SDL/releases/download/release-2.30.1/SDL2-devel-2.30.1-VC.zip")

# Set the extract directory for downloaded SDL library.
set(SDL2_EXTRACTION_DIRECTORY "${CMAKE_SOURCE_DIR}/dependencies/SDL2")

# Download and extract SDL library.
include(FetchContent)
FetchContent_Declare(SDL2 URL ${SDL2_DOWNLOAD_URL} SOURCE_DIR ${SDL2_EXTRACTION_DIRECTORY})
FetchContent_MakeAvailable(SDL2)

# Add 'include' folder as header directory.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(bomberman_remake src/main.c
        src/debugger.c)
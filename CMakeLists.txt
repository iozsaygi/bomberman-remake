cmake_minimum_required(VERSION 3.27)
project(bomberman_remake C)

set(CMAKE_C_STANDARD 23)

# Update module path for easier script locating for CMake.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

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

find_package(SDL2 REQUIRED)

# Add SDL as include directory.
include_directories(${SDL2_INCLUDE_DIRECTORIES})

add_executable(bomberman_remake src/main.c
        src/debugger.c
        src/game.c
        src/scene.c)

# Link the SDL library.
target_link_libraries(bomberman_remake PRIVATE ${SDL2_LIBRARIES})
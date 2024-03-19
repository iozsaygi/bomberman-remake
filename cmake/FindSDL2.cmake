set(SDL2_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/dependencies/SDL2/include/")

if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARIES "${CMAKE_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2.lib;${CMAKE_SOURCE_DIR}/dependencies/SDL2/lib/x64/SDL2main.lib")
else ()
    message(FATAL_ERROR "Failed to set SDL2 libraries for current architecture")
endif ()

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
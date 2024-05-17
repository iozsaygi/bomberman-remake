#include "asset_manager.h"
#include "debugger.h"

#include <SDL.h>
#include <stdio.h>

struct assetManager_textures assetManager_textures;

// Function to load a BMP file from a specified path
SDL_Surface* loadBMP(const char* filePath) {
    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    // Load BMP image
    SDL_Surface* loadedSurface = SDL_LoadBMP(filePath);
    if (loadedSurface == NULL) {
        printf("Unable to load BMP file %s! SDL_Error: %s\n", filePath, SDL_GetError());
    }

    // Quit SDL subsystems
    SDL_Quit();

    return loadedSurface;
}

enum assetManager_assetOperationResult assetManager_loadTextures() {
    assetManager_textures.textureAtlas = SDL_LoadBMP(TEXTURE_ATLAS_PATH);
    if (assetManager_textures.textureAtlas == NULL) {
        debugger_log(CRITICAL, "Failed to load texture atlas, the following error received: %s", SDL_GetError());
        return ASSETS_FAILED_TO_LOAD;
    }

    return ASSETS_LOADED;
}

void assetManager_clear() {
    SDL_FreeSurface(assetManager_textures.textureAtlas);
    debugger_log(TRACE, "Removed loaded assets from memory");
}
#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SDL.h>

#define TEXTURE_ATLAS_PATH "assets/textures/texture_atlas.bmp"

enum assetManager_assetOperationResult {
    ASSETS_LOADED,
    ASSETS_FAILED_TO_LOAD
};

struct assetManager_textures {
    SDL_Surface* textureAtlas;
};

extern struct assetManager_textures assetManager_textures;

enum assetManager_assetOperationResult assetManager_loadTextures();
void assetManager_clear();

#endif// !ASSET_MANAGER_H
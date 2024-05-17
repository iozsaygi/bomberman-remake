#include "asset_manager.h"
#include "debugger.h"

struct assetManager_textures assetManager_textures;

enum assetManager_assetOperationResult assetManager_loadTextures(struct game_platformContext gamePlatformContext) {
    assetManager_textures.textureAtlasSurface = SDL_LoadBMP(TEXTURE_ATLAS_PATH);
    if (assetManager_textures.textureAtlasSurface == NULL) {
        debugger_log(CRITICAL, "Failed to load texture atlas as surface, the following error received: %s", SDL_GetError());
        return ASSETS_FAILED_TO_LOAD;
    }

    assetManager_textures.textureAtlas = SDL_CreateTextureFromSurface(gamePlatformContext.renderer, assetManager_textures.textureAtlasSurface);
    if (assetManager_textures.textureAtlas == NULL) {
        debugger_log(CRITICAL, "Failed to load texture atlas from surface, the following error received: %s", SDL_GetError());
        return ASSETS_FAILED_TO_LOAD;
    }

    return ASSETS_LOADED;
}

void assetManager_clear() {
    SDL_FreeSurface(assetManager_textures.textureAtlasSurface);
    SDL_DestroyTexture(assetManager_textures.textureAtlas);
    debugger_log(TRACE, "Removed loaded assets from memory");
}
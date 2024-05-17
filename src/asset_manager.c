#include "asset_manager.h"
#include "debugger.h"

struct assetManager_textures assetManager_textures;

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
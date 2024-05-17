#include "asset_manager.h"
#include "scene.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Try to initialize dependencies first.
    if (game_initializeDependencies() == FAILURE) {
        return -1;
    }

    // Try to load assets before entering the scene context.
    // Do not launch the game if asset operations are failed.
    if (assetManager_loadTextures(game_platformContext) == ASSETS_FAILED_TO_LOAD) {
        scanf("%d");
        return -1;
    }

    // Try to create platform context.
    if (game_createPlatformContext(352, 288, "Bomberman: Remake", 15) == SUCCESS) {
        scene_initialize();
        // We have the game's platform context here. Start to update scene.
        scene_tick(game_platformContext);

        // Clear the platform context after the main loop, we are done with it.
        game_clearPlatformContext();
    }

    // Clear loaded assets.
    assetManager_clear();

    // Terminate initialized game dependencies.
    game_terminateDependencies();

    return 0;
}
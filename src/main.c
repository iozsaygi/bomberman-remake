#include "scene.h"

int main(int argc, char* argv[]) {
    // Try to initialize dependencies first.
    if (game_initializeDependencies() == FAILURE) {
        return -1;
    }

    // Try to create platform context.
    if (game_createPlatformContext(320, 256, "Bomberman: Remake", 15) == SUCCESS) {
        scene_initialize();
        // We have the game's platform context here. Start to update scene.
        scene_tick(game_platformContext);

        // Clear the platform context after the main loop, we are done with it.
        game_clearPlatformContext();
    }

    // Terminate initialized game dependencies.
    game_terminateDependencies();

    return 0;
}
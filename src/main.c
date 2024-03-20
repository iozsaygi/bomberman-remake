#include "game.h"

int main(int argc, char* argv[]) {
    // Try to initialize dependencies first.
    if (game_initializeDependencies() == FAILURE) {
        return -1;
    }

    // Try to create platform context.
    if (game_createPlatformContext(640, 480, "Bomberman Remake") == SUCCESS) {
        // We have the game's platform context here. Start to update scene.

        // Clear the platform context after the main loop, we are done with it.
        game_clearPlatformContext();
    }

    // Terminate initialized game dependencies.
    game_terminateDependencies();

    return 0;
}
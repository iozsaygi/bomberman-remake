#include "scene.h"
#include "debugger.h"
#include "event_dispatcher.h"
#include "map.h"
#include "player.h"

struct bomb_transform* scene_lastPlantedBomb;

void scene_initialize() {
    player_initialize();
    map_initialize();
    scene_lastPlantedBomb = NULL;

    // Allocate the bomb. (It will be invisible)
    struct vector2 bombAllocationPosition;
    bombAllocationPosition.x = -100;
    bombAllocationPosition.y = -100;
    scene_lastPlantedBomb = bomb_createAt(bombAllocationPosition);
}

void scene_requestBombAt(struct vector2 position) {
    // Explode the last planted bomb first.
    bomb_explode(scene_lastPlantedBomb);
    bomb_plantAt(position, scene_lastPlantedBomb);
    debugger_log(TRACE, "Placed a new bomb at (%d, %d)", position.x, position.y);
}

void scene_tick(struct game_platformContext gamePlatformContext) {
    unsigned char tickFlag = 1;
    const int targetFrameDelay = 1000 / gamePlatformContext.targetFrameRate;

    Uint32 prevFrameTime = SDL_GetTicks();

    while (tickFlag == 1) {
        Uint32 frameStart = SDL_GetTicks();

        enum eventDispatcher_eventType frameEvent = eventDispatcher_handleEvents();
        if (frameEvent == SHUTDOWN || frameEvent == KEY_DOWN_ESCAPE) {
            tickFlag = 0;
        }

        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (float) (currentFrameTime - prevFrameTime) / 1000.0f;
        prevFrameTime = currentFrameTime;

        // Update order with delta time
        player_tick(gamePlatformContext, frameEvent, deltaTime);
        if (scene_lastPlantedBomb != NULL) {
            bomb_tick(deltaTime, scene_lastPlantedBomb);
        }

        SDL_SetRenderDrawColor(gamePlatformContext.renderer, 46, 138, 1, 255);
        SDL_RenderClear(gamePlatformContext.renderer);

        // Render order.
        map_render(gamePlatformContext, assetManager_textures);
        player_render(gamePlatformContext, assetManager_textures);
        if (scene_lastPlantedBomb != NULL) {
            bomb_render(gamePlatformContext, scene_lastPlantedBomb, assetManager_textures);
        }

        SDL_RenderPresent(gamePlatformContext.renderer);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (targetFrameDelay > frameTime) {
            SDL_Delay(targetFrameDelay - frameTime);
        }
    }
}

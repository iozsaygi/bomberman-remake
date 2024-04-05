#include "scene.h"
#include "event_dispatcher.h"
#include "map.h"
#include "player.h"

void scene_initialize() {
    player_initialize();
    map_initialize();
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
        player_tick(frameEvent, deltaTime);

        SDL_SetRenderDrawColor(gamePlatformContext.renderer, 46, 138, 1, 255);
        SDL_RenderClear(gamePlatformContext.renderer);

        // Render order.
        map_render(gamePlatformContext);
        player_render(gamePlatformContext);

        SDL_RenderPresent(gamePlatformContext.renderer);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (targetFrameDelay > frameTime) {
            SDL_Delay(targetFrameDelay - frameTime);
        }
    }
}

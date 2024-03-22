#include "scene.h"
#include "event_dispatcher.h"
#include "player.h"

void scene_initialize() {
    player_initialize();
}

void scene_tick(struct game_platformContext gamePlatformContext) {
    unsigned char tickFlag = 1;

    while (tickFlag == 1) {
        enum eventDispatcher_eventType frameEvent = eventDispatcher_handleEvents();
        if (frameEvent == SHUTDOWN) {
            tickFlag = 0;
        }

        SDL_RenderClear(gamePlatformContext.renderer);
        SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0x00, 0x00, 0x00, 0x00);

        // Render player first.
        player_render(gamePlatformContext);

        SDL_RenderPresent(gamePlatformContext.renderer);
    }
}
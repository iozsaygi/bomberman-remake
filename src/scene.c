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

    while (tickFlag == 1) {
        enum eventDispatcher_eventType frameEvent = eventDispatcher_handleEvents();
        if (frameEvent == SHUTDOWN || frameEvent == KEY_DOWN_ESCAPE) {
            tickFlag = 0;
        }

        // Update order.
        player_tick(frameEvent);

        SDL_SetRenderDrawColor(gamePlatformContext.renderer, 46, 138, 1, 255);
        SDL_RenderClear(gamePlatformContext.renderer);

        // Render order.
        map_render(gamePlatformContext);
        player_render(gamePlatformContext);

        SDL_RenderPresent(gamePlatformContext.renderer);
    }
}
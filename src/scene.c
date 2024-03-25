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

        SDL_RenderClear(gamePlatformContext.renderer);
        SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0x00, 0x00, 0x00, 0xFF);

        // Render order.
        player_render(gamePlatformContext);
        map_render(gamePlatformContext);

        SDL_RenderPresent(gamePlatformContext.renderer);
    }
}
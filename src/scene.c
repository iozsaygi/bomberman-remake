#include "scene.h"

void scene_tick(struct game_platformContext gamePlatformContext) {
    unsigned char tickFlag = 1;

    SDL_Event event;
    while (tickFlag == 1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                tickFlag = 0;
            }
        }

        SDL_RenderClear(gamePlatformContext.renderer);
        SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0x00, 0x00, 0x00, 0x00);

        SDL_RenderPresent(gamePlatformContext.renderer);
    }
}
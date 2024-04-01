#include "map.h"

struct node map_nodes[MAP_WIDTH][MAP_HEIGHT];

void map_initialize() {
}

void map_render(struct game_platformContext gamePlatformContext) {
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 255, 255, 255, 255);
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 0, 0, 255);
}
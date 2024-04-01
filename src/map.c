#include "map.h"

struct node map_nodes[MAP_WIDTH][MAP_HEIGHT];

void map_initialize() {
    struct node dummyNode = {
            .id = {.context = 0},
            .position = {.x = 150, .y = 140},
            .neighbors = {.context = 1}};

    map_nodes[0] = dummyNode;
}

void map_render(struct game_platformContext gamePlatformContext) {
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 255, 255, 255, 255);
    SDL_Rect renderRect;
    renderRect.w = NODE_SCALE;
    renderRect.h = NODE_SCALE;
    renderRect.x = map_nodes[0].position.x;
    renderRect.y = map_nodes[0].position.y;
    SDL_RenderDrawRect(gamePlatformContext.renderer, &renderRect);
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 0, 0, 255);
}
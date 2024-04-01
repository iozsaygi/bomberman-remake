#include "map.h"

struct node map_nodes[MAP_WIDTH][MAP_HEIGHT];

void map_initialize() {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            // Calculate the ID of the node.
            int id = x * MAP_HEIGHT + y;

            // Assign the node ID.
            map_nodes[x][y].id.context = id;

            // Calculate the position of the node.
            map_nodes[x][y].position.x = (float) (x * NODE_SCALE);
            map_nodes[x][y].position.y = (float) (y * NODE_SCALE);

            //
        }
    }
}

void map_render(struct game_platformContext gamePlatformContext) {
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 255, 255, 255, 255);

    // Render the each node we have.
    // TODO: Reduce the render calls by using line renderer. This is 300 render calls at the moment.
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            SDL_Rect renderRect;
            renderRect.x = (int) (map_nodes[x][y].position.x);
            renderRect.y = (int) (map_nodes[x][y].position.y);
            renderRect.w = NODE_SCALE;
            renderRect.h = NODE_SCALE;

            SDL_RenderDrawRect(gamePlatformContext.renderer, &renderRect);
        }
    }

    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 0, 0, 255);
}
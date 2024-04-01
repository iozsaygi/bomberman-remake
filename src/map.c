#include "map.h"
#include "debugger.h"

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

            // Calculate and assign possible neighbors.
            // Top neighbor.
            if (y == 0) {
                map_nodes[x][y].neighbors[0].context = NODE_INVALID_NEIGHBOR_ID;
            } else {
                map_nodes[x][y].neighbors[0].context = x * MAP_HEIGHT + (y - 1);
            }

            // Bottom neighbor.
            if (y == MAP_HEIGHT - 1) {
                map_nodes[x][y].neighbors[1].context = NODE_INVALID_NEIGHBOR_ID;
            } else {
                map_nodes[x][y].neighbors[1].context = x * MAP_HEIGHT + (y + 1);
            }

            // Left neighbor.
            if (x == 0) {
                map_nodes[x][y].neighbors[2].context = NODE_INVALID_NEIGHBOR_ID;
            } else {
                map_nodes[x][y].neighbors[2].context = (x - 1) * MAP_HEIGHT + y;
            }

            // Right neighbor.
            if (x == MAP_WIDTH - 1) {
                map_nodes[x][y].neighbors[3].context = NODE_INVALID_NEIGHBOR_ID;
            } else {
                map_nodes[x][y].neighbors[3].context = (x + 1) * MAP_HEIGHT + y;
            }
        }
    }

    debugger_log(TRACE, "Initialized the game map with %d nodes", MAP_WIDTH * MAP_HEIGHT);
}

void map_convertNodeIDToCoordinate(int id, int* x, int* y) {
    // TODO: Ensure that this works correctly.
    *x = id / MAP_HEIGHT;
    *y = id % MAP_HEIGHT;
}

void map_render(struct game_platformContext gamePlatformContext) {
    // Render the each node we have.
    // TODO: Reduce the render calls by using line renderer. This is 300 render calls at the moment.
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            SDL_Rect renderRect;
            renderRect.x = (int) (map_nodes[x][y].position.x);
            renderRect.y = (int) (map_nodes[x][y].position.y);
            renderRect.w = NODE_SCALE;
            renderRect.h = NODE_SCALE;

            // TODO: This is for neighbor debugging, remove later.
            if (map_nodes[x][y].id.context == 25) {
                for (int i = 0; i < NODE_NEIGHBOR_CAPACITY; i++) {
                    if (map_nodes[x][y].neighbors[i].context != NODE_INVALID_NEIGHBOR_ID) {
                        SDL_Rect neighborRect;
                        neighborRect.w = NODE_SCALE;
                        neighborRect.h = NODE_SCALE;
                        int cx, cy;
                        map_convertNodeIDToCoordinate(map_nodes[x][y].neighbors[i].context, &cx, &cy);
                        neighborRect.x = (int) (map_nodes[cx][cy].position.x);
                        neighborRect.y = (int) (map_nodes[cx][cy].position.y);

                        SDL_SetRenderDrawColor(gamePlatformContext.renderer, 255, 0, 0, 255);
                        SDL_RenderDrawRect(gamePlatformContext.renderer, &neighborRect);
                    }
                }
            } else {
                SDL_SetRenderDrawColor(gamePlatformContext.renderer, 20, 20, 20, 255);
                SDL_RenderDrawRect(gamePlatformContext.renderer, &renderRect);
            }
        }
    }
}
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

            // Assign the node context.
            map_nodes[x][y].nodeContext = NONE;

            // Calculate the position of the node.
            map_nodes[x][y].position.x = (float) (x * NODE_SCALE);
            map_nodes[x][y].position.y = (float) (y * NODE_SCALE);

            // Calculate and assign possible neighbors.
            // Top neighbor.
            if (y > 0) {
                map_nodes[x][y].neighbors[0].context = x * MAP_HEIGHT + (y - 1);
            } else {
                map_nodes[x][y].neighbors[0].context = NODE_INVALID_NEIGHBOR_ID;
            }

            // Bottom neighbor.
            if (y < MAP_HEIGHT - 1) {
                map_nodes[x][y].neighbors[1].context = x * MAP_HEIGHT + (y + 1);
            } else {
                map_nodes[x][y].neighbors[1].context = NODE_INVALID_NEIGHBOR_ID;
            }

            // Left neighbor.
            if (x > 0) {
                map_nodes[x][y].neighbors[2].context = (x - 1) * MAP_HEIGHT + y;
            } else {
                map_nodes[x][y].neighbors[2].context = NODE_INVALID_NEIGHBOR_ID;
            }

            // Right neighbor.
            if (x < MAP_WIDTH - 1) {
                map_nodes[x][y].neighbors[3].context = (x + 1) * MAP_HEIGHT + y;
            } else {
                map_nodes[x][y].neighbors[3].context = NODE_INVALID_NEIGHBOR_ID;
            }
        }
    }

    debugger_log(TRACE, "Initialized the game map with %d nodes", MAP_WIDTH * MAP_HEIGHT);
}

void map_render(struct game_platformContext gamePlatformContext) {
    // Render each node and its neighbors
    // TODO: Optimize or remove this later on. It is 300 renders calls at the moment.
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            struct node current = map_nodes[x][y];
            SDL_Rect renderRect;
            renderRect.w = NODE_SCALE;
            renderRect.h = NODE_SCALE;
            renderRect.x = (int) current.position.x;
            renderRect.y = (int) current.position.y;
            SDL_SetRenderDrawColor(gamePlatformContext.renderer, 10, 10, 10, 255);
            SDL_RenderDrawRect(gamePlatformContext.renderer, &renderRect);
        }
    }
}
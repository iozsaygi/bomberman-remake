#include "map.h"
#include "debugger.h"
#include <stdlib.h>
#include <time.h>

int map_blockedNodeIDs[BLOCKED_NODE_COUNT] = {
        10,
        28,
        46,
        64,
        82,
        12,
        30,
        48,
        66,
        84,
        14,
        32,
        50,
        68,
        86,
        16,
        34,
        52,
        70,
        88,
};

struct node map_nodes[MAP_WIDTH][MAP_HEIGHT];

void map_initialize() {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            // Calculate the ID of the node.
            int id = x * MAP_HEIGHT + y;

            // Assign the node ID.
            map_nodes[x][y].id.context = id;

            // Assign the node context.
            if (map_isNodeBlocked(map_nodes[x][y].id) == 1) {
                map_nodes[x][y].nodeContext = BLOCKED;
            } else {
                map_nodes[x][y].nodeContext = AVAILABLE;
            }

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

    // map_setupRandomizedBlockedNodes(10);

    debugger_log(TRACE, "Initialized the game map with %d nodes", MAP_WIDTH * MAP_HEIGHT);
}

void map_setupRandomizedBlockedNodes(int count) {
    srand(time(NULL));

    for (int i = 0; i < count; i++) {
        int randomRow = rand() % MAP_WIDTH;
        int randomColumn = rand() % MAP_HEIGHT;
        map_nodes[randomColumn][randomRow].nodeContext = BLOCKED;
    }
}

int map_isNodeBlocked(struct node_id nodeID) {
    // Simple linear search to see if node with given ID is blocked or not.
    for (int i = 0; i < BLOCKED_NODE_COUNT; i++) {
        if (nodeID.context == map_blockedNodeIDs[i]) {
            return 1;
        }
    }

    return 0;
}

struct node map_positionToNode(struct vector2 position) {
    struct node result;
    int horizontalIndex = (int) (position.x / NODE_SCALE);
    int verticalIndex = (int) (position.y / NODE_SCALE);

    if (horizontalIndex >= 0 && horizontalIndex < MAP_WIDTH && verticalIndex >= 0 && verticalIndex < MAP_HEIGHT) {
        result = map_nodes[horizontalIndex][verticalIndex];
    }

    return result;
}

void map_render(struct game_platformContext gamePlatformContext, struct assetManager_textures textures) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            struct node current = map_nodes[x][y];
            SDL_Rect renderRect;
            renderRect.w = NODE_SCALE;
            renderRect.h = NODE_SCALE;
            renderRect.x = (int) current.position.x;
            renderRect.y = (int) current.position.y;
            if (current.nodeContext == BLOCKED) {
                SDL_Rect textureRenderRect;
                textureRenderRect.x = 48;
                textureRenderRect.y = 48;
                textureRenderRect.w = 16;
                textureRenderRect.h = 17;
                SDL_RenderCopy(gamePlatformContext.renderer, textures.textureAtlas, &textureRenderRect, &renderRect);
            }
        }
    }
}
#ifndef MAP_H
#define MAP_H

#include "game.h"
#include "node.h"

// Game window is 320x240, each node has 16 pixel for height and width.
// The map is going to fully allocate the entire game window.
// Map size is -> (352 / 32) x (288 / 32) = (10) x (9) = 99
#define MAP_WIDTH 11
#define MAP_HEIGHT 9
#define BLOCKED_NODE_COUNT 20

extern int map_blockedNodeIDs[BLOCKED_NODE_COUNT];
extern struct node map_nodes[MAP_WIDTH][MAP_HEIGHT];

void map_initialize();

void map_setupRandomizedBlockedNodes(int count);
int map_isNodeBlocked(struct node_id nodeID);
struct node map_positionToNode(struct vector2 position);

void map_render(struct game_platformContext gamePlatformContext);

#endif// !MAP_H
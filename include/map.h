#ifndef MAP_H
#define MAP_H

#include "game.h"
#include "node.h"

// Game window is 320x240, each node has 16 pixel for height and width.
// The map is going to fully allocate the entire game window.
// Map size is -> (320 / 32) x (288 / 32) = (10) x (9) = 90
#define MAP_WIDTH 10
#define MAP_HEIGHT 9

extern struct node map_nodes[MAP_WIDTH][MAP_HEIGHT];

void map_initialize();

void map_render(struct game_platformContext gamePlatformContext);

#endif// !MAP_H
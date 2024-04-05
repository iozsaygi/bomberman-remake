#ifndef MAP_H
#define MAP_H

#include "game.h"
#include "node.h"

// Game window is 320x240, each node has 16 pixel for height and width.
// The map is going to fully allocate the entire game window.
// Map size is -> (320 / 32) x (256 / 32) = (10) x (8) = 80
#define MAP_WIDTH 10
#define MAP_HEIGHT 8
#define MAP_LENGTH 80

extern struct node map_nodes[MAP_WIDTH][MAP_HEIGHT];

void map_initialize();

void map_render(struct game_platformContext gamePlatformContext);

#endif// !MAP_H
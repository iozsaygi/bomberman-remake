#ifndef MAP_H
#define MAP_H

#include "game.h"
#include "node.h"

// Game window is 320x240, each node has 16 pixel for height and width.
// The map is going to fully allocate the entire game window.
// Map size is -> (320 / 16) x (240 / 16) = (20) x (15) = 300
#define MAP_LENGTH 300

extern struct node map_nodes[MAP_LENGTH];

void map_initialize();
void map_render(struct game_platformContext gamePlatformContext);

#endif// !MAP_H
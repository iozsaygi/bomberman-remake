#ifndef MAP_H
#define MAP_H

#include "game.h"
#include "node.h"

extern struct node map_nodes[1];

void map_initialize();
void map_render(struct game_platformContext gamePlatformContext);

#endif// !MAP_H
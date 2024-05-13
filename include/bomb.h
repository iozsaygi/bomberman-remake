#ifndef BOMB_H
#define BOMB_H

#include "game.h"
#include "vector2.h"

struct bomb_transform {
    struct vector2 position;
};

void bomb_createAt(struct vector2 position);
void bomb_tick(float deltaTime);
void bomb_render(struct game_platformContext gamePlatformContext);

#endif// !BOMB_H
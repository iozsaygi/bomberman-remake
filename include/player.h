#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "vector2.h"

struct player_transform {
    struct vector2 position;
    struct vector2 scale;
};

extern struct player_transform player_transform;

// Will be called when the scene is getting initialized.
void player_initialize();

// Will be called on each render pass.
void player_render(struct game_platformContext gamePlatformContext);

#endif// !PLAYER_H
#ifndef BOMB_H
#define BOMB_H

#include "asset_manager.h"
#include "game.h"
#include "vector2.h"

#define BOMB_LIFETIME_IN_SECONDS 3

struct bomb_transform {
    struct vector2 position;
    struct vector2 scale;
    float timer;
    unsigned char isExploded;
};

struct bomb_transform* bomb_createAt(struct vector2 position);
void bomb_tick(float deltaTime, struct bomb_transform* bombTransform);
void bomb_plantAt(struct vector2 position, struct bomb_transform* bombTransform);
void bomb_explode(struct bomb_transform* bombTransform);
void bomb_render(struct game_platformContext gamePlatformContext, struct bomb_transform* bombTransform, struct assetManager_textures textures);

#endif// !BOMB_H
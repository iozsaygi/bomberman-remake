#ifndef ENEMY_H
#define ENEMY_H

#include "asset_manager.h"
#include "game.h"
#include "vector2.h"

struct enemy_transform {
    struct vector2 position;
    struct vector2 scale;
};

extern int enemy_shrinkCount;

struct enemy_transform* enemy_initialize(struct vector2 position, struct vector2 scale);
void enemy_tick(struct enemy_transform* enemyTransform, float deltaTime);
void enemy_shrink(struct enemy_transform* enemyTransform);
void enemy_render(struct game_platformContext gamePlatformContext, struct enemy_transform* enemyTransform, struct assetManager_textures textures);

#endif// !ENEMY_H
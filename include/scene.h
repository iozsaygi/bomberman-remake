#ifndef SCENE_H
#define SCENE_H

#include "bomb.h"
#include "enemy.h"
#include "game.h"

// TODO: Convert this to a buffer to support multiple bomb placements.
extern struct bomb_transform* scene_lastPlantedBomb;

extern struct enemy_transform* scene_enemyTransform;

void scene_initialize();
void scene_requestBombAt(struct vector2 position);
void scene_tick(struct game_platformContext gamePlatformContext);

#endif// !SCENE_H
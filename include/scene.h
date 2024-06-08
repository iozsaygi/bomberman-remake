#ifndef SCENE_H
#define SCENE_H

#include "bomb.h"
#include "enemy.h"
#include "game.h"

#define ENEMY_COUNT 3

// TODO: Convert this to a buffer to support multiple bomb placements.
extern struct bomb_transform* scene_lastPlantedBomb;

extern struct enemy_transform* scene_enemyTransforms[ENEMY_COUNT];

void scene_initialize();
void scene_requestBombAt(struct vector2 position);
void scene_placeEnemies();
void scene_reset();
void scene_tick(struct game_platformContext gamePlatformContext);
void scene_getEnemiesInExplosionRange(struct vector2 origin, float range, struct enemy_transform* results[ENEMY_COUNT]);
void scene_shutdown();

#endif// !SCENE_H
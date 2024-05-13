#ifndef SCENE_H
#define SCENE_H

#include "game.h"
#include "bomb.h"

// TODO: Convert this to a buffer to support multiple bomb placements.
extern struct bomb_transform* scene_lastPlantedBomb;

void scene_initialize();
void scene_requestBombAt(struct vector2 position);
void scene_tick(struct game_platformContext gamePlatformContext);

#endif// !SCENE_H
#include "enemy.h"
#include <stdlib.h>

struct enemy_transform* enemy_initialize(struct vector2 position, struct vector2 scale) {
    struct enemy_transform* enemyTransform = (struct enemy_transform*) malloc(sizeof(struct enemy_transform));
    enemyTransform->position = position;
    enemyTransform->scale = scale;
    return enemyTransform;
}

void enemy_tick(float deltaTime) {
}

void enemy_render(struct game_platformContext gamePlatformContext, struct enemy_transform* enemyTransform, struct assetManager_textures textures) {
}
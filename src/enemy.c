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
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 255, 0, 255);
    SDL_Rect renderTransformRect;
    renderTransformRect.w = (int) enemyTransform->scale.x;
    renderTransformRect.h = (int) enemyTransform->scale.y;
    renderTransformRect.x = (int) enemyTransform->position.x;
    renderTransformRect.y = (int) enemyTransform->position.y;

    SDL_Rect textureRenderRect;
    textureRenderRect.x = 0;
    textureRenderRect.y = 240;
    textureRenderRect.w = 16;
    textureRenderRect.h = 16;

    SDL_RenderCopy(gamePlatformContext.renderer, textures.textureAtlas, &textureRenderRect, &renderTransformRect);

    // Well, no idea how we need this. The main loop in scene should already handle color resetting
    // for each render pass.
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 0, 0, 255);
}
#include "bomb.h"
#include "debugger.h"
#include "entity_props.h"
#include "scene.h"
#include <assert.h>
#include <stdlib.h>

struct bomb_transform* bomb_createAt(struct vector2 position) {
    // Try to allocate bomb first.
    struct bomb_transform* bombTransform = (struct bomb_transform*) malloc(sizeof(struct bomb_transform));
    assert(bombTransform != NULL);
    bombTransform->position = position;
    bombTransform->scale.x = BOMB_SCALE;
    bombTransform->scale.y = BOMB_SCALE;
    bombTransform->timer = 0.0f;
    bombTransform->isExploded = 1;

    return bombTransform;
}

void bomb_tick(float deltaTime, struct bomb_transform* bombTransform) {
    if (bombTransform->isExploded == 1) {
        return;
    }

    bombTransform->timer += deltaTime;
    if (bombTransform->timer >= BOMB_LIFETIME_IN_SECONDS) {
        bomb_explode(bombTransform);
    }
}

void bomb_plantAt(struct vector2 position, struct bomb_transform* bombTransform) {
    bombTransform->scale.x = DEFAULT_ENTITY_SCALE / 2;
    bombTransform->scale.y = DEFAULT_ENTITY_SCALE / 2;
    bombTransform->position = position;
    bombTransform->isExploded = 0;
    bombTransform->timer = 0.0f;
}

void bomb_explode(struct bomb_transform* bombTransform) {
    // Do not explode if it is already exploded.
    if (bombTransform->isExploded == 1) {
        return;
    }

    bombTransform->scale.x = 0.0f;
    bombTransform->scale.y = 0.0f;
    bombTransform->isExploded = 1;

    struct enemy_transform* result[ENEMY_COUNT];

    // TODO: 'Range' is temporarily hard-coded.
    debugger_log(TRACE, "bomb-0");
    scene_getEnemiesInExplosionRange(bombTransform->position, 5.0f, result);
    debugger_log(TRACE, "bomb-1");
    for (int i = 0; i < ENEMY_COUNT; i++) {
        debugger_log(TRACE, "bomb-2");
        if (result[i] != NULL) {
            debugger_log(TRACE, "bomb-3");
            enemy_shrink(result[i]);
        }
    }
    debugger_log(TRACE, "bomb-5");
}

void bomb_render(struct game_platformContext gamePlatformContext, struct bomb_transform* bombTransform, struct assetManager_textures textures) {
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 255, 0, 0, 255);

    SDL_Rect renderTransformRect;
    renderTransformRect.w = (int) bombTransform->scale.x * 2;
    renderTransformRect.h = (int) bombTransform->scale.y * 2;
    renderTransformRect.x = (int) bombTransform->position.x;
    renderTransformRect.y = (int) bombTransform->position.y;

    SDL_Rect textureRenderRect;
    textureRenderRect.x = 0;
    textureRenderRect.y = 48;
    textureRenderRect.w = 17;
    textureRenderRect.h = 17;

    SDL_RenderCopy(gamePlatformContext.renderer, textures.textureAtlas, &textureRenderRect, &renderTransformRect);

    // Well, no idea how we need this. The main loop in scene should already handle color resetting
    // for each render pass.
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 0, 0, 255);
}
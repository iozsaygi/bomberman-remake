#include "bomb.h"
#include "entity_props.h"
#include <assert.h>
#include <stdlib.h>

struct bomb_transform* bomb_createAt(struct vector2 position) {
    // Try to allocate bomb first.
    struct bomb_transform* bombTransform = (struct bomb_transform*) malloc(sizeof(struct bomb_transform));
    assert(bombTransform != NULL);
    bombTransform->position = position;
    bombTransform->scale.x = DEFAULT_ENTITY_SCALE / 2;
    bombTransform->scale.y = DEFAULT_ENTITY_SCALE / 2;

    return bombTransform;
}

void bomb_tick(float deltaTime) {
}

void bomb_explode(struct bomb_transform* bombTransform) {
    assert(bombTransform != NULL);
    // TODO: Apply damage to adjacent nodes.
    free(bombTransform);
}

void bomb_render(struct game_platformContext gamePlatformContext, struct bomb_transform* bombTransform) {
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 255, 0, 255);
    SDL_Rect renderRect;
    renderRect.w = (int) bombTransform.scale.x;
    renderRect.h = (int) bombTransform.scale.y;
    renderRect.x = (int) bombTransform.position.x;
    renderRect.y = (int) bombTransform.position.y;

    SDL_RenderFillRect(gamePlatformContext.renderer, &renderRect);

    // Well, no idea how we need this. The main loop in scene should already handle color resetting
    // for each render pass.
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 0, 0, 255);
}
#include "bomb.h"
#include <assert.h>
#include <stdlib.h>

struct bomb_transform* bomb_createAt(struct vector2 position) {
    // Try to allocate bomb first.
    struct bomb_transform* bombTransform = (struct bomb_transform*) malloc(sizeof(struct bomb_transform));
    assert(bombTransform != NULL);
    bombTransform->position = position;

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
}
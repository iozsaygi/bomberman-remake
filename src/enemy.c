#include "enemy.h"
#include "debugger.h"
#include "physics.h"
#include "player.h"
#include "scene.h"
#include <stdlib.h>
#include "entity_props.h"

int enemy_shrinkCount = 0;

struct enemy_transform* enemy_initialize(struct vector2 position, struct vector2 scale) {
    struct enemy_transform* enemyTransform = (struct enemy_transform*) malloc(sizeof(struct enemy_transform));
    enemyTransform->position = position;
    enemyTransform->scale = scale;
    enemyTransform->movementDirection = NONE;
    return enemyTransform;
}

void enemy_tick(struct enemy_transform* enemyTransform, float deltaTime) {
    // Check for collision against player.
    struct physics_collisionBox playerCollisionBox;
    playerCollisionBox.w = (int) player_transform.scale.x;
    playerCollisionBox.h = (int) player_transform.scale.y;
    playerCollisionBox.x = (int) player_transform.position.x;
    playerCollisionBox.y = (int) player_transform.position.y;

    struct physics_collisionBox enemyCollisionBox;
    enemyCollisionBox.w = (int) enemyTransform->scale.x;
    enemyCollisionBox.h = (int) enemyTransform->scale.y;
    enemyCollisionBox.x = (int) enemyTransform->position.x;
    enemyCollisionBox.y = (int) enemyTransform->position.y;

    enum physics_collisionOpResult opResult = physics_boundingBoxCollisionQuery(&playerCollisionBox, &enemyCollisionBox);
    if (opResult == ACTIVE_COLLISION) {
        scene_reset();
    }

    // Check for screen collision.
    if (enemyTransform->position.x <= 0) {
        enemyTransform->movementDirection = MD_RIGHT;
    } else if (enemyTransform->position.x >= (float)game_platformContext.width + DEFAULT_ENTITY_SCALE) {
        enemyTransform->movementDirection = MD_LEFT;
    } else if (enemyTransform->position.y <= 0) {
        enemyTransform->movementDirection = MD_DOWN;
    } else if (enemyTransform->position.y >= (float)game_platformContext.height + DEFAULT_ENTITY_SCALE) {
        enemyTransform->movementDirection = MD_UP;
    }

    // Movement.
    const float movementSpeed = 20.0f;
    switch (enemyTransform->movementDirection) {
        case MD_UP:
            enemyTransform->position.y -= movementSpeed * deltaTime;
            break;
        case MD_DOWN:
            enemyTransform->position.y += movementSpeed * deltaTime;
            break;
        case MD_LEFT:
            enemyTransform->position.x -= movementSpeed * deltaTime;
            break;
        case MD_RIGHT:
            enemyTransform->position.x += movementSpeed * deltaTime;
            break;
        case MD_NONE:
            break;
    }
}

void enemy_shrink(struct enemy_transform* enemyTransform) {
    // Move the enemy to a weird location.
    enemyTransform->position.x = 800;
    enemyTransform->position.y = 800;

    enemy_shrinkCount++;
    if (enemy_shrinkCount == ENEMY_COUNT) {
        enemy_shrinkCount = 0;
        scene_placeEnemies();
    }
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
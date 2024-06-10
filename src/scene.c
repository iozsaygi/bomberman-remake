#include "scene.h"
#include "debugger.h"
#include "event_dispatcher.h"
#include "map.h"
#include "physics.h"
#include "player.h"
#include <assert.h>
#include <stdlib.h>

struct bomb_transform* scene_lastPlantedBomb;
struct enemy_transform* scene_enemyTransforms[ENEMY_COUNT];

void scene_initialize() {
    player_initialize();
    map_initialize();
    scene_lastPlantedBomb = NULL;

    // Allocate the bomb. (It will be invisible)
    struct vector2 bombAllocationPosition;
    bombAllocationPosition.x = -100;
    bombAllocationPosition.y = -100;
    scene_lastPlantedBomb = bomb_createAt(bombAllocationPosition);

    // Allocate the enemies.
    for (int i = 0; i < ENEMY_COUNT; i++) {
        scene_enemyTransforms[i] = malloc(sizeof(struct enemy_transform));
        assert(scene_enemyTransforms[i] != NULL);
        struct vector2 enemyPosition;
        enemyPosition.x = 0;
        enemyPosition.y = 0;
        struct vector2 enemyScale;
        enemyScale.x = DEFAULT_ENTITY_SCALE;
        enemyScale.y = DEFAULT_ENTITY_SCALE;
        scene_enemyTransforms[i] = enemy_initialize(enemyPosition, enemyScale);
    }

    // Manually initialize enemy positions, change it to randomized version later.
    scene_placeEnemies();
}

void scene_requestBombAt(struct vector2 position) {
    // Explode the last planted bomb first.
    bomb_explode(scene_lastPlantedBomb);
    bomb_plantAt(position, scene_lastPlantedBomb);
    debugger_log(TRACE, "Placed a new bomb at (%d, %d)", position.x, position.y);
}

void scene_placeEnemies() {
    scene_enemyTransforms[0]->position.x = 320;
    scene_enemyTransforms[0]->position.y = 140;
    scene_enemyTransforms[0]->movementDirection = MD_LEFT;
    scene_enemyTransforms[1]->position.x = 240;
    scene_enemyTransforms[1]->position.y = 0;
    scene_enemyTransforms[1]->movementDirection = MD_LEFT;
    scene_enemyTransforms[2]->position.x = 0;
    scene_enemyTransforms[2]->position.y = 240;
    scene_enemyTransforms[2]->movementDirection = MD_UP;
}

void scene_reset() {
    scene_placeEnemies();
    player_initialize();
}

void scene_tick(struct game_platformContext gamePlatformContext) {
    unsigned char tickFlag = 1;
    const int targetFrameDelay = 1000 / gamePlatformContext.targetFrameRate;

    Uint32 prevFrameTime = SDL_GetTicks();

    while (tickFlag == 1) {
        Uint32 frameStart = SDL_GetTicks();

        enum eventDispatcher_eventType frameEvent = eventDispatcher_handleEvents();
        if (frameEvent == SHUTDOWN || frameEvent == KEY_DOWN_ESCAPE) {
            tickFlag = 0;
        }

        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (float) (currentFrameTime - prevFrameTime) / 1000.0f;
        prevFrameTime = currentFrameTime;

        // Update order with delta time
        player_tick(gamePlatformContext, frameEvent, deltaTime);
        if (scene_lastPlantedBomb != NULL) {
            bomb_tick(deltaTime, scene_lastPlantedBomb);
        }

        for (int i = 0; i < ENEMY_COUNT; i++) {
            enemy_tick(scene_enemyTransforms[i], deltaTime);
        }

        SDL_SetRenderDrawColor(gamePlatformContext.renderer, 46, 138, 1, 255);
        SDL_RenderClear(gamePlatformContext.renderer);

        // Render order.
        map_render(gamePlatformContext, assetManager_textures);

        for (int i = 0; i < ENEMY_COUNT; i++) {
            enemy_render(gamePlatformContext, scene_enemyTransforms[i], assetManager_textures);
        }

        if (scene_lastPlantedBomb != NULL) {
            bomb_render(gamePlatformContext, scene_lastPlantedBomb, assetManager_textures);
        }

        player_render(gamePlatformContext, assetManager_textures);
        SDL_RenderPresent(gamePlatformContext.renderer);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (targetFrameDelay > frameTime) {
            SDL_Delay(targetFrameDelay - frameTime);
        }
    }
}

void scene_getEnemiesInExplosionRange(struct vector2 origin, float range, struct enemy_transform* results[ENEMY_COUNT]) {
    for (int i = 0; i < ENEMY_COUNT; i++) {
        float distance = physics_getDistance(origin, scene_enemyTransforms[i]->position);
        if (distance < range) {
            results[i] = scene_enemyTransforms[i];
        }
    }
}

void scene_shutdown() {
    for (int i = 0; i < ENEMY_COUNT; i++) {
        free(scene_enemyTransforms[i]);
    }
}
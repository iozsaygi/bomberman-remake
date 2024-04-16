#ifndef PLAYER_H
#define PLAYER_H

#include "event_dispatcher.h"
#include "game.h"
#include "vector2.h"

struct player_transform {
    struct vector2 position;
    struct vector2 scale;
};

struct player_movement {
    float speed;
};

enum player_transformOperationResult {
    CAN_MOVE,
    CAN_NOT_MOVE
};

extern struct player_transform player_transform;
extern struct player_movement player_movement;

// Will be called when the scene is getting initialized.
void player_initialize();

void player_tick(struct game_platformContext gamePlatformContext, enum eventDispatcher_eventType frameEvent, float deltaTime);
enum player_transformOperationResult player_checkBlockedNodeIntersection(struct vector2 possiblePosition);

// Will be called on each render pass.
void player_render(struct game_platformContext gamePlatformContext);

#endif// !PLAYER_H
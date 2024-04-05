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

extern struct player_transform player_transform;
extern struct player_movement player_movement;

// Will be called when the scene is getting initialized.
void player_initialize();

void player_tick(enum eventDispatcher_eventType frameEvent, float deltaTime);

// Will be called on each render pass.
void player_render(struct game_platformContext gamePlatformContext);

#endif// !PLAYER_H
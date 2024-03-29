#include "player.h"
#include "entity_props.h"

struct player_transform player_transform;
struct player_movement player_movement;

void player_initialize() {
    player_transform.position.x = 120;
    player_transform.position.y = 100;
    player_transform.scale.x = DEFAULT_ENTITY_SCALE * 1;
    player_transform.scale.y = DEFAULT_ENTITY_SCALE * 1;
    player_movement.speed = 5.0f;
}

void player_tick(enum eventDispatcher_eventType frameEvent) {
    switch (frameEvent) {
        case KEY_DOWN_W:
            player_transform.position.y -= player_movement.speed;
            break;
        case KEY_DOWN_A:
            player_transform.position.x -= player_movement.speed;
            break;
        case KEY_DOWN_S:
            player_transform.position.y += player_movement.speed;
            break;
        case KEY_DOWN_D:
            player_transform.position.x += player_movement.speed;
            break;
        case NONE:
            break;
        case SHUTDOWN:
            break;
        case KEY_DOWN_SPACE:
            break;
    }
}

void player_render(struct game_platformContext gamePlatformContext) {
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 255, 0, 255);
    SDL_Rect renderRect;
    renderRect.w = player_transform.scale.x;
    renderRect.h = player_transform.scale.y;
    renderRect.x = player_transform.position.x;
    renderRect.y = player_transform.position.y;

    SDL_RenderFillRect(gamePlatformContext.renderer, &renderRect);

    // Well, no idea how we need this. The main loop in scene should already handle color resetting
    // for each render pass.
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 0, 0, 255);
}
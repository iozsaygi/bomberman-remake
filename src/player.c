#include "player.h"
#include "debugger.h"
#include "entity_props.h"

struct player_transform player_transform;
struct player_movement player_movement;

void player_initialize() {
    player_transform.position.x = 0;
    player_transform.position.y = 0;
    player_transform.scale.x = PLAYER_SCALE;
    player_transform.scale.y = PLAYER_SCALE;
    player_movement.speed = 125.0f;
}

void player_tick(struct game_platformContext gamePlatformContext, enum eventDispatcher_eventType frameEvent, float deltaTime) {
    struct vector2 desiredPosition = player_transform.position;

    switch (frameEvent) {
        case KEY_DOWN_W:
            desiredPosition.y -= player_movement.speed * deltaTime;
            if (desiredPosition.y >= 0 && desiredPosition.y <= (float) gamePlatformContext.height) {
                player_transform.position = desiredPosition;
            } else {
                // Calculate the gap.
                float verticalGap = desiredPosition.y;
                desiredPosition.y -= verticalGap;
                player_transform.position = desiredPosition;
            }
            break;
        case KEY_DOWN_A:
            desiredPosition.x -= player_movement.speed * deltaTime;
            if (desiredPosition.x >= 0 && desiredPosition.x <= (float) gamePlatformContext.width) {
                player_transform.position = desiredPosition;
            } else {
                // Calculate the gap.
                float horizontalGap = desiredPosition.x;
                desiredPosition.x -= horizontalGap;
                player_transform.position = desiredPosition;
            }
            break;
        case KEY_DOWN_S:
            desiredPosition.y += player_movement.speed * deltaTime;
            if (desiredPosition.y + PLAYER_SCALE <= (float) gamePlatformContext.height) {
                player_transform.position = desiredPosition;
            } else {
                // Calculate the gap.
                float verticalGap = (float) (gamePlatformContext.height) - (desiredPosition.y + PLAYER_SCALE);
                desiredPosition.y += verticalGap;
                player_transform.position = desiredPosition;
            }
            break;
        case KEY_DOWN_D:
            desiredPosition.x += player_movement.speed * deltaTime;
            if (desiredPosition.x + PLAYER_SCALE <= (float) gamePlatformContext.width) {
                player_transform.position = desiredPosition;
            } else {
                // Calculate the gap.
                float horizontalGap = (float) gamePlatformContext.width - (desiredPosition.x + PLAYER_SCALE);
                desiredPosition.x += horizontalGap;
                player_transform.position = desiredPosition;
            }
            break;
        case NONE:
            break;
        case SHUTDOWN:
            break;
        case KEY_DOWN_SPACE:
            break;
        case KEY_DOWN_ESCAPE:
            break;
    }
}

void player_render(struct game_platformContext gamePlatformContext) {
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 255, 0, 255);
    SDL_Rect renderRect;
    renderRect.w = (int) player_transform.scale.x;
    renderRect.h = (int) player_transform.scale.y;
    renderRect.x = (int) player_transform.position.x;
    renderRect.y = (int) player_transform.position.y;

    SDL_RenderFillRect(gamePlatformContext.renderer, &renderRect);

    // Well, no idea how we need this. The main loop in scene should already handle color resetting
    // for each render pass.
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 0, 0, 255);
}
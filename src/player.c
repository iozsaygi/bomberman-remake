#include "player.h"
#include "entity_props.h"

struct player_transform player_transform;

void player_initialize() {
    player_transform.position.x = 360;
    player_transform.position.y = 150;
    player_transform.scale.x = DEFAULT_ENTITY_SCALE * 1;
    player_transform.scale.y = DEFAULT_ENTITY_SCALE * 1;
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
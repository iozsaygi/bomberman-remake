#include "player.h"
#include "debugger.h"
#include "entity_props.h"
#include "map.h"
#include "physics.h"
#include "scene.h"

struct player_transform player_transform;
struct player_movement player_movement;

unsigned char player_isSpaceKeyRegisteredForCurrentFrame;

void player_initialize() {
    player_transform.position.x = 0;
    player_transform.position.y = 0;
    player_transform.scale.x = PLAYER_SCALE;
    player_transform.scale.y = PLAYER_SCALE;
    player_movement.speed = 125.0f;
}

void player_tick(struct game_platformContext gamePlatformContext, enum eventDispatcher_eventType frameEvent, float deltaTime) {
    struct vector2 desiredPosition = player_transform.position;

    struct physics_collisionBox desiredCollisionBox;
    desiredCollisionBox.w = PLAYER_SCALE;
    desiredCollisionBox.h = PLAYER_SCALE;

    switch (frameEvent) {
        case KEY_DOWN_W:
            desiredPosition.y -= player_movement.speed * deltaTime;

            desiredCollisionBox.x = (int) desiredPosition.x;
            desiredCollisionBox.y = (int) desiredPosition.y;

            struct node upwardNode = map_positionToNode(desiredPosition);
            struct physics_collisionBox upwardNodeCollisionBox;
            upwardNodeCollisionBox.w = NODE_SCALE;
            upwardNodeCollisionBox.h = NODE_SCALE;
            upwardNodeCollisionBox.x = (int) upwardNode.position.x;
            upwardNodeCollisionBox.y = (int) upwardNode.position.y;

            if (upwardNode.nodeContext == BLOCKED && physics_boundingBoxCollisionQuery(&desiredCollisionBox, &upwardNodeCollisionBox) == ACTIVE_COLLISION) {
                return;
            }

            // If no collision with the upwardNode, proceed with movement
            if (desiredPosition.y >= 0 && desiredPosition.y <= (float) gamePlatformContext.height) {
                player_transform.position = desiredPosition;// Set the player's position
            } else {
                // Adjust the player's position if it goes beyond the game window
                float verticalGap = desiredPosition.y;
                desiredPosition.y -= verticalGap;
                player_transform.position = desiredPosition;
            }

            break;
        case KEY_DOWN_A:
            desiredPosition.x -= player_movement.speed * deltaTime;

            desiredCollisionBox.x = (int) desiredPosition.x;
            desiredCollisionBox.y = (int) desiredPosition.y;

            struct node leftNode = map_positionToNode(desiredPosition);
            struct physics_collisionBox leftNodeCollisionBox;
            leftNodeCollisionBox.w = NODE_SCALE;
            leftNodeCollisionBox.h = NODE_SCALE;
            leftNodeCollisionBox.x = (int) leftNode.position.x;
            leftNodeCollisionBox.y = (int) leftNode.position.y;

            if (leftNode.nodeContext == BLOCKED && physics_boundingBoxCollisionQuery(&desiredCollisionBox, &leftNodeCollisionBox) == ACTIVE_COLLISION) {
                return;
            }

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

            desiredCollisionBox.x = (int) desiredPosition.x;
            desiredCollisionBox.y = (int) desiredPosition.y;

            struct node downNode = map_positionToNode(desiredPosition);
            struct physics_collisionBox downNodeCollisionBox;
            downNodeCollisionBox.w = NODE_SCALE;
            downNodeCollisionBox.h = NODE_SCALE;
            downNodeCollisionBox.x = (int) downNode.position.x;
            downNodeCollisionBox.y = (int) downNode.position.y;

            if (downNode.nodeContext == BLOCKED && physics_boundingBoxCollisionQuery(&desiredCollisionBox, &downNodeCollisionBox) == ACTIVE_COLLISION) {
                return;
            }

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

            desiredCollisionBox.x = (int) desiredPosition.x;
            desiredCollisionBox.y = (int) desiredPosition.y;

            struct node rightNode = map_positionToNode(desiredPosition);
            struct physics_collisionBox rightNodeCollisionBox;
            rightNodeCollisionBox.w = NODE_SCALE;
            rightNodeCollisionBox.h = NODE_SCALE;
            rightNodeCollisionBox.x = (int) rightNode.position.x;
            rightNodeCollisionBox.y = (int) rightNode.position.y;

            if (rightNode.nodeContext == BLOCKED && physics_boundingBoxCollisionQuery(&desiredCollisionBox, &rightNodeCollisionBox) == ACTIVE_COLLISION) {
                return;
            }

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
            if (player_isSpaceKeyRegisteredForCurrentFrame == 0) {
                struct node targetNode = map_positionToNode(player_transform.position);
                scene_requestBombAt(targetNode.position);
                player_isSpaceKeyRegisteredForCurrentFrame = 1;
            }
            break;
        case KEY_DOWN_ESCAPE:
            break;
        case KEY_UP_SPACE:
            if (player_isSpaceKeyRegisteredForCurrentFrame == 1) {
                player_isSpaceKeyRegisteredForCurrentFrame = 0;
            }
            break;
    }
}

void player_render(struct game_platformContext gamePlatformContext, struct assetManager_textures textures) {
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 255, 0, 255);
    SDL_Rect renderTransformRect;
    renderTransformRect.w = (int) player_transform.scale.x;
    renderTransformRect.h = (int) player_transform.scale.y;
    renderTransformRect.x = (int) player_transform.position.x;
    renderTransformRect.y = (int) player_transform.position.y;

    SDL_Rect texture_rect;
    texture_rect.x = 60; //the x coordinate
    texture_rect.y = 0; //the y coordinate
    texture_rect.w = 12; //the width of the texture
    texture_rect.h = 12; //the height of the texture

    SDL_RenderCopy(gamePlatformContext.renderer, textures.textureAtlas, &texture_rect, &renderTransformRect);

    // Well, no idea how we need this. The main loop in scene should already handle color resetting
    // for each render pass.
    SDL_SetRenderDrawColor(gamePlatformContext.renderer, 0, 0, 0, 255);
}
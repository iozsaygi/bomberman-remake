#include "physics.h"
#include <math.h>

enum physics_collisionOpResult physics_boundingBoxCollisionQuery(struct physics_collisionBox* first, struct physics_collisionBox* second) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = first->x;
    rightA = first->x + first->w;
    topA = first->y;
    bottomA = first->y + first->h;

    leftB = second->x;
    rightB = second->x + second->w;
    topB = second->y;
    bottomB = second->y + second->h;

    if (bottomA < topB) {
        return NO_COLLISION;
    }

    if (topA > bottomB) {
        return NO_COLLISION;
    }

    if (rightA <= leftB) {
        return NO_COLLISION;
    }

    if (leftA >= rightB) {
        return NO_COLLISION;
    }

    return ACTIVE_COLLISION;
}

float physics_getDistance(struct vector2 first, struct vector2 second) {
    float deltaX = second.x - first.x;
    float deltaY = second.y - first.y;
    return sqrtf(deltaX * deltaX + deltaY * deltaY);
}
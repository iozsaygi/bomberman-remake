#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector2.h"

enum physics_collisionOpResult {
    ACTIVE_COLLISION,
    NO_COLLISION
};

// Just a basic wrapper over 'SDL_Rect' structure.
struct physics_collisionBox {
    int w;
    int h;
    int x;
    int y;
};

enum physics_collisionOpResult physics_boundingBoxCollisionQuery(struct physics_collisionBox* first, struct physics_collisionBox* second);
float physics_getDistance(struct vector2 first, struct vector2 second);

#endif// !PHYSICS_H
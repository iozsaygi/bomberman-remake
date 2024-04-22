#ifndef PHYSICS_H
#define PHYSICS_H

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

#endif// !PHYSICS_H
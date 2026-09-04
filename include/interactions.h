#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "xEngine.h"
#include "world.h"

#define WORLD_GRID_SIZE 64
#define PLAYER_TARGET_RANGE 3

typedef struct InteractionTarget
{
    xVector2 grid;

    Entity *entity;

    bool valid;

} InteractionTarget;

void xUpdateInteraction(InteractionTarget *target, World *world, xCamera2D camera, xVector2 playerPos);

#endif
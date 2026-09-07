#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "xEngine.h"
#include "world.h"

#define WORLD_GRID_SIZE 64
#define PLAYER_TARGET_RANGE 1

typedef struct InteractionTarget
{
    xVector2 grid;      // Grid position.

    Entity *entity;     // Pointer to entity.

    bool valid;         // Whether an interaction is valid.

} InteractionTarget;

/// Update player-object interactions.
void xUpdateInteraction(InteractionTarget *target, World *world, xCamera2D camera, xVector2 playerPos);

#endif
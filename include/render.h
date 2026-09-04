#ifndef RENDER_H
#define RENDER_H

#include "player.h"
#include "world.h"
#include "animal.h"
#include "interactions.h"

/// Render the scene with all game objects.
void xRenderScene(World *world, Player *player, AnimalManager *manager);

/// Render interaction target. 
void xRenderInteractionTarget(const InteractionTarget *target);

#endif
#ifndef RENDER_H
#define RENDER_H

#include "xEngine.h"
#include "player.h"
#include "world.h"
#include "animal.h"

/// Renders the scene with player and game objects.
void xRenderScene(World *world, Player *player, Animal *animal);

#endif
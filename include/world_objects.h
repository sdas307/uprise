#ifndef WORLD_OBJECT_H
#define WORLD_OBJECTS_H

#include "world.h"
#include "xEngine.h"

/* ---------- Signatures ---------- */

void xAddStone(World *world, StoneType type, xRectangle dest);

void xAddTree(World *world, TreeStage stage, xRectangle dest);

void xAddHouse(World *world, xRectangle dest);

void xAddLightPost(World *world, xRectangle dest);

void xAddRock(World *world, RockType type, xRectangle dest);

void xLoadTreesLarge(World *world);

void xLoadTreesSmall(World *world);

void xAddMushroom(World *world, xRectangle dest);

#endif
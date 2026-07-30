#ifndef ENTITIES_H
#define ENTITIES_H

#include "world.h"
#include "xEngine.h"

/* ---------- Signatures ---------- */

void xAddStone(World *world, StoneType type, xRectangle dest);

void xAddTree(World *world, TreeStage stage, xRectangle dest);

void xAddHouse(World *world, xRectangle dest);

void xAddLightPost(World *world, xRectangle dest);

void xAddRock(World *world, RockType type, xRectangle dest);

void xAddMushroom(World *world, xRectangle dest);

void xAddPond6x6(World *world, xRectangle dest);

void xAddGroundBlock(World *world, xRectangle dest);

void xAddEmptyEntity(World *world, xRectangle dest);

void xAddHighGroundTopLeft(World *world, xRectangle dest);

void xAddHighGroundTopCenter(World *world, xRectangle dest);

void xAddHighGroundTopRight(World *world, xRectangle dest);

void xAddHighGroundCenterLeft(World *world, xRectangle dest);

void xAddHighGroundCenterCenter(World *world, xRectangle dest);

void xAddHighGroundCenterRight(World *world, xRectangle dest);

void xAddHighGroundBottomLeft(World *world, xRectangle dest);

void xAddHighGroundBottomCenter(World *world, xRectangle dest);

void xAddHighGroundBottomRight(World *world, xRectangle dest);

#endif
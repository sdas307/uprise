#ifndef ENTITIES_H
#define ENTITIES_H

#include "world.h"
#include "xEngine.h"

void xAddStone(World *world, StoneType type, xRectangle dest);

void xAddTree(World *world, TreeStage stage, xRectangle dest);

void xAddHouse(World *world, xRectangle dest);

void xAddLightPost(World *world, xRectangle dest);

void xAddRock(World *world, RockType type, xRectangle dest);

void xAddMushroom(World *world, xRectangle dest);

void xAddPond6x6(World *world, xRectangle dest);

void xAddGroundBlock(World *world, xRectangle dest);

void xAddFlower(World *world, FlowerColor color, FlowerType type, xRectangle dest);

void xAddEmptyEntity(World *world, xRectangle dest);

#endif
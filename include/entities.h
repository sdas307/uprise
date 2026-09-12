#ifndef ENTITIES_H
#define ENTITIES_H

#include "world.h"
#include "xEngine.h"


void xAddTree(World *world, TreeType type, TreeStage stage, xRectangle dest);

void xAddHouse(World *world, HouseType type, xRectangle dest);

void xAddLightPost(World *world, xRectangle dest);

void xAddUpperLayerColliders(World *world, int index, xRectangle dest);

void xAddStairs(World *world, xRectangle dest);

void xAddHedge(World *world, HedgePiece piece, xRectangle dest);

void xAddFlower(World *world, FlowerColor color, FlowerType type, xRectangle dest);

void xAddCliffStairsCollider(World *world, xRectangle dest);

void xAddCliffCollider(World *world, int index, xRectangle dest);

void xAddFarmland(World *world, int index, xRectangle dest);

#endif
#ifndef ENTITIES_H
#define ENTITIES_H

#include "world.h"
#include "xEngine.h"

void xAddStone(World *world, StoneType type, xRectangle dest);

void xAddTree(World *world, TreeType type, TreeStage stage, xRectangle dest);

void xAddHouse(World *world, HouseType type, xRectangle dest);

void xAddLightPost(World *world, xRectangle dest);

void xAddRock(World *world, RockType type, xRectangle dest);

void xAddGrass(World *world, GrassVariant variant, xRectangle dest);

void xAddMushroom(World *world, MushroomType type, xRectangle dest);

void xAddHighGroundBounds(World *world, xRectangle dest);

void xAddStairs(World *world, xRectangle dest);

void xAddHedge(World *world, HedgePiece piece, xRectangle dest);

void xAddWildflowers(World *world, WildflowerVariant variant, xRectangle dest);

void xAddFlower(World *world, FlowerColor color, FlowerType type, xRectangle dest);

void xAddEmptyEntity(World *world, xRectangle dest);

#endif
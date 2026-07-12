#ifndef BASE_H
#define BASE_H

#include "xEngine.h"
#include "world_objects.h"

#define MAX_TREES 32

typedef struct BaseConfig
{
    xRectangle largeTrees[MAX_TREES];
    int largeTreesCount;

    xRectangle smallTrees[MAX_TREES];
    int smallTreesCount;

} BaseConfig;

extern xRectangle largeTrees[MAX_TREES];

void xBaseInit(BaseConfig *config);

bool xLoadBaseConfig(BaseConfig *config);

/// Loads all large trees at their world positions.
void xLoadTreesLarge(World *world);

/// Loads all small trees at their world positions.
void xLoadTreesSmall(World *world);

/// Loads house at world positions.
void xLoadHouse(World *world);

#endif
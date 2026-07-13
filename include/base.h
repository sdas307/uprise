#ifndef BASE_H
#define BASE_H

#include "xEngine.h"
#include "world_objects.h"

/// Loads all large trees at their world positions.
void xLoadTreesLarge(World *world);

/// Loads all small trees at their world positions.
void xLoadTreesSmall(World *world);

/// Loads house at world positions.
void xLoadHouse(World *world);

#endif
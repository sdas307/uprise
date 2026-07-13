#include "base.h"
#include "assets.h"

/* ---------- Destination Rectangles ----------*/

static const xRectangle largeTrees[] =
{
    { 64*5 + 15, -32, 64 * 3 - 27, 64 * 4 },
    { 64*6 +  8, -32, 64 * 3 - 27, 64 * 4 },
    { 64*9 + 16, -32, 64 * 3 - 27, 64 * 4 },
    { 64*10 + 12, -32, 64 * 3 - 27, 64 * 4 }
    
};

static const xRectangle house =
{
    64*2 - 12,
    -58,
    64*5 - 40,
    64*7
};

static const xRectangle smallTrees[] =
{
    { 64-9, 64*4 + 20, 64*2 - 34, 64*2 }
};

/* ---------------------------------------------*/

/// Loads all large trees at their world positions.
static void xLoadTreesLarge(World *world)
{
    for (int i=0; i<ARRAY_COUNT(largeTrees); i++)
    {
        xAddTree(world, TREE_LARGE, largeTrees[i]);
    }
}

/// Loads all small trees at their world positions.
static void xLoadTreesSmall(World *world)
{
    for (int i=0; i<ARRAY_COUNT(smallTrees); i++)
    {
        xAddTree(world, TREE_SMALL, smallTrees[i]);
    }
}

/// Loads house at world positions.
static void xLoadHouse(World *world)
{
    xAddHouse(world, house);
}

void xLoadBaseMap(World *world, AnimalManager *manager)
{
    xLoadTreesLarge(world);

    xLoadHouse(world);

    xLoadTreesSmall(world);

    xAddLightPost(world, (xRectangle){64*6 + 16, 64*4, SPRITE_LIGHT_POST.width, SPRITE_LIGHT_POST.height});

    xAddRock(world, ROCK_SMALL, (xRectangle){64*2 - 26, 64*6 - 21, SPRITE_ROCK_SMALL.width, SPRITE_ROCK_SMALL.height });

    xSpawnCow(manager, (xRectangle){464, 400-128, SPRITE_COW.width, SPRITE_COW.height});

    xSpawnChicken(manager, (xRectangle){400, 400, SPRITE_CHICKEN.width, SPRITE_CHICKEN.height});
}
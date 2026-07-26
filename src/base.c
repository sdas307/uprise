#include "base.h"
#include "assets.h"
#include "sprites.h"

#pragma region Destination Rectangles
static const xVector2 posLargeTrees[] =
{
    {64 * 5 + 15, -32},
    {64 * 6 +  8, -32},
    {64 * 9 + 16, -32},
    {64 * 10 + 12, -32}
};

static const xRectangle posSmallTrees[] =
{
    {64-9, 64*4 + 20}
};

static const xVector2 posHouse[] =
{
    {64 * 2 - 12, -58}
};

static const xVector2 posGroundBlocks[] =
{
    { 832, 64 }
};

#pragma endregion

/// Loads all large trees at their world positions.
static void xLoadTreesLarge(World *world)
{
    for (int i=0; i<ARRAY_COUNT(posLargeTrees); i++)
    {
        xRectangle temp =
        {
            posLargeTrees[i].x,
            posLargeTrees[i].y,
            RECT_TREE_LARGE.width,
            RECT_TREE_LARGE.height
        };

        xAddTree(world, TREE_LARGE, temp);
    }
}

/// Loads all small trees at their world positions.
static void xLoadTreesSmall(World *world)
{
    for (int i=0; i<ARRAY_COUNT(posSmallTrees); i++)
    {
        xRectangle temp =
        {
            posSmallTrees[i].x,
            posSmallTrees[i].y,
            RECT_TREE_SMALL.width,
            RECT_TREE_SMALL.height
        };

        xAddTree(world, TREE_SMALL, temp);
    }
}

/// Loads house at world positions.
static void xLoadHouse(World *world)
{
    xRectangle temp =
    {
        posHouse[0].x,
        posHouse[0].y,
        RECT_HOUSE.width,
        RECT_HOUSE.height
    };
    
    xAddHouse(world, temp);
}

static void xLoadLightPost(World *world)
{
    xRectangle dest =
    {
        64 * 6 + 16,
        64 * 4,
        RECT_LIGHT_POST.width,
        RECT_LIGHT_POST.height
    };

    xAddLightPost(world, dest);
}

static void xLoadRocks(World *world)
{
    xRectangle dest =
    {
        64*2 - 26,
        64*6 - 21,
        RECT_ROCK_SMALL.width,
        RECT_ROCK_SMALL.height
    };

    xAddRock(world, ROCK_SMALL, dest);
}

static void xLoadAnimals(AnimalManager *manager)
{
    xRectangle dest =
    {
        464,
        400-128,
        RECT_COW.width,
        RECT_COW.height
    };
    xSpawnCow(manager, dest);

    dest = (xRectangle)
    {
        400,
        400,
        RECT_CHICKEN.width,
        RECT_CHICKEN.height
    };
    xSpawnChicken(manager, dest);
}

static void xLoadGroundBlocks(World *world)
{

    xRectangle dest =
    {
        posGroundBlocks[0].x,
        posGroundBlocks[0].y,
        RECT_GROUND_BLOCK.width,
        RECT_GROUND_BLOCK.height
    };

    xAddGroundBlock(world, dest);
}

void xLoadBaseMap(World *world, AnimalManager *manager)
{
    xLoadTreesLarge(world);
    xLoadHouse(world);
    xLoadTreesSmall(world);
    xLoadGroundBlocks(world);
    xLoadRocks(world);
    xLoadLightPost(world);
    xLoadAnimals(manager);
}
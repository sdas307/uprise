#include "base.h"
#include "assets.h"
#include "sprites.h"
#include "animal.h"
#include "base_data.h"

/// Load all large trees at their world coordinates.
static void xLoadTreesLarge(World *world)
{
    for (int i=0; i<treesLargeCount; i++)
    {
        xRectangle temp =
        {
            treesLarge[i].x,
            treesLarge[i].y,
            RECT_TREE_LARGE.width,
            RECT_TREE_LARGE.height
        };

        xAddTree(world, TREE_LARGE, temp);
    }
}

/// Load all small trees at their world coordinates.
static void xLoadTreesSmall(World *world)
{
    for (int i=0; i<treesSmallCount; i++)
    {
        xRectangle temp =
        {
            treesSmall[i].x,
            treesSmall[i].y,
            RECT_TREE_SMALL.width,
            RECT_TREE_SMALL.height
        };

        xAddTree(world, TREE_SMALL, temp);
    }
}

/// Load house at world coordinates.
static void xLoadHouse(World *world)
{
    xRectangle temp =
    {
        house[0].x,
        house[0].y,
        RECT_HOUSE.width,
        RECT_HOUSE.height
    };

    xAddHouse(world, temp);
}

/// Load light posts at world coordinates.
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

/// Load rocks at world coordinates.
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

/// Load animals at world coordinates.
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
        764,
        640,
        RECT_SHEEP.width,
        RECT_SHEEP.height
    };
    xSpawnSheep(manager, dest);

    dest = (xRectangle)
    {
        640,
        632,
        RECT_PIG.width,
        RECT_PIG.height
    };
    xSpawnPig(manager, dest);

    dest = (xRectangle)
    {
        700,
        600,
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

    dest = (xRectangle)
    {
        464,
        400,
        RECT_CHICKEN.width,
        RECT_CHICKEN.height
    };
    xSpawnChicken(manager, dest);

    dest = (xRectangle)
    {
        600,
        464,
        RECT_CHICKEN.width,
        RECT_CHICKEN.height
    };
    xSpawnChicken(manager, dest);

    dest = (xRectangle)
    {
        650,
        500,
        RECT_CHICKEN.width,
        RECT_CHICKEN.height
    };
    xSpawnChicken(manager, dest);
}

/// Load ground blocks at world coordinates.
static void xLoadGroundBlocks(World *world)
{

    xRectangle dest =
    {
        groundBlocks[0].x,
        groundBlocks[0].y,
        RECT_GROUND_BLOCK.width,
        RECT_GROUND_BLOCK.height
    };

    xAddGroundBlock(world, dest);
}

static void xHighGroundColliders(World *world, xRectangle const highGround[])
{
    // Top row
    xRectangle collider =
    {
        highGround[0].x + 48,
        highGround[0].y + 28,
        highGround[0].width - 48,
        highGround[0].height - 40,
    };
    xAddEmptyEntity(world, collider);

    // Left column
    collider = (xRectangle)
    {
        highGround[1].x + 28,
        highGround[1].y - 16,
        highGround[1].width - 44,
        highGround[1].height - 32,
    };
    xAddEmptyEntity(world, collider);

    // Bottom row
    collider = (xRectangle)
    {
        highGround[2].x - 16,
        highGround[2].y + 16,
        highGround[2].width + 16,
        highGround[2].height - 48,
    };
    xAddEmptyEntity(world, collider);
}

/// Load all elements of base map in their world positions. 
void xLoadBaseMap(World *world, AnimalManager *manager)
{
    xHighGroundColliders(world, highGround);
    // xLoadHighGround(world);
    xLoadTreesLarge(world);
    xLoadHouse(world);
    xLoadTreesSmall(world);
    xLoadGroundBlocks(world);
    xLoadRocks(world);
    xLoadLightPost(world);
    xLoadAnimals(manager);
}
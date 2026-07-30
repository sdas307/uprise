#include "base.h"
#include "assets.h"
#include "sprites.h"
#include "animal.h"

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

// Collider rects for high ground.
static const xRectangle highGround[] =
{
    {   0,   0, 1024,  64 },
    {   0,  64,   64, 704 },
    {  64, 704,  640,  64 },
    { 896, 704,  128,  64 },
};

#pragma endregion

/// Load all large trees at their world coordinates.
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

/// Load all small trees at their world coordinates.
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

/// Load house at world coordinates.
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
}

/// Load ground blocks at world coordinates.
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

#pragma region Load High Ground (Inactive Function)
/// Load high ground terrain blocks at world coordinates.
static void xLoadHighGround(World *world)
{
    // Top-Left
    xRectangle dest =
    {
        0,
        0,
        64,
        64
    };
    xAddHighGroundTopLeft(world, dest);

    // Bottom-Left
    dest = (xRectangle)
    {
        0,
        GetScreenHeight() - 64,
        64,
        64
    }; 
    xAddHighGroundBottomLeft(world, dest);

    // Bottom-Right
    dest = (xRectangle)
    {
        GetScreenWidth() - 64,
        GetScreenHeight() - 64,
        64,
        64
    };
    xAddHighGroundBottomRight(world, dest);

    // Top-Right
    dest = (xRectangle)
    {
        GetScreenWidth() - 64,
        0,
        64,
        64
    };
    xAddHighGroundTopRight(world, dest);

    // Top high ground blocks
    for (int i = 1; i <= 14; i++)
    {
        xRectangle temp =
        {
            i * 64,
            0,
            64,
            64
        };

        xAddHighGroundTopCenter(world, temp);
    }

    // Left high ground blocks
    for (int i = 1; i <= 11; i++)
    {
        xRectangle temp =
        {
            0,
            i * 64,
            64,
            64
        };

        xAddHighGroundCenterLeft(world, temp);
    }

    // Bottom high ground blocks
    for (int i = 1; i <= 14; i++)
    {
        xRectangle temp =
        {
            i * 64,
            768,
            64,
            64
        };

        xAddHighGroundBottomCenter(world, temp);
    }
}
#pragma endregion

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

    // Bottom row (leftover)
    collider = (xRectangle)
    {
        highGround[3].x,
        highGround[3].y + 16,
        highGround[3].width - 48,
        highGround[3].height - 48,
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
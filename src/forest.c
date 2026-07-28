#include "forest.h"
#include "assets.h"
#include "sprites.h"

#pragma region Forest Entities Destination Rectangles

static const xVector2 posLargeTrees[] =
{
    { 900, -88 },
    { 840, -88 },
    { 896, 124 },
    { 896, 220 },
    { 896, 316 },
    { 896, 412 },
    { 896, 508 },
    { 252, 432 },
    { 204, 516 },
    { 332, 516 },
    { 616, 360 },
    { 676, 360 },
};

static const xVector2 posTreeCuts[] =
{
    { 888, 680 },
};

static const xVector2 posPonds[] =
{
    { 320, 256 },
};

static const xVector2 posGroundBlocks[] =
{
    { 0, 0 },
};

static const xVector2 posLogs[] =
{
    { 796, 84 },
};

static const xVector2 posMushrooms[] =
{
    { 592, 596 },
    { 656, 596 },
    { 304, 124 },
    { 240, 124 },
    { 176, 124 },
    { 844, 32 },
};

static const xVector2 posRocksSmall[] =
{
    { 712, 340 },
};

static const xVector2 posSmallTrees[] =
{
    { 112, 0 },
    { 176, 0 },
    { 240, 0 },
    { 304, 0 },
    { 112, 64 },
    { 176, 64 },
    { 240, 64 },
    { 304, 64 },
};

static const xVector2 posTreeStumps[] =
{
    { 68, 128 },
};

static const xVector2 posFlowerYellow[] =
{
    { 208, 656 },
};
#pragma endregion

/* ---------- Implementation ----------*/

/// Load large trees at their world coordinates.
static void xLoadTreesLarge1(World *world)
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

/// Load small trees at their world coordinates.
static void xLoadTreesSmall1(World *world)
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

/// Load mushrooms at their world coordinates.
static void xLoadMushrooms(World *world)
{
    for (int i=0; i<ARRAY_COUNT(posMushrooms); i++)
    {
        xRectangle temp =
        {
            posMushrooms[i].x,
            posMushrooms[i].y,
            RECT_MUSHROOM.width,
            RECT_MUSHROOM.height
        };

        xAddMushroom(world, temp);
    }
}

/// Load rocks at their world coordinates.
static void xLoadRocks(World *world)
{
    for (int i=0; i<ARRAY_COUNT(posRocksSmall); i++)
    {
        xRectangle temp =
        {
            posRocksSmall[i].x,
            posRocksSmall[i].y,
            RECT_ROCK_SMALL.width,
            RECT_ROCK_SMALL.height
        };

        xAddRock(world, ROCK_SMALL, temp);
    }
}

/// Load cut trees at their world coordinates.
static void xLoadTreesCut(World *world)
{
    for (int i=0; i<ARRAY_COUNT(posTreeCuts); i++)
    {
        xRectangle temp =
        {
            posTreeCuts[i].x,
            posTreeCuts[i].y,
            RECT_TREE_CUT.width,
            RECT_TREE_CUT.height
        };

        xAddTree(world, TREE_CUT, temp);
    }
}

/// Load tree stumps at their world coordinates.
static void xLoadTreesStump(World *world)
{
    for (int i=0; i<ARRAY_COUNT(posTreeStumps); i++)
    {
        xRectangle temp =
        {
            posTreeStumps[i].x,
            posTreeStumps[i].y,
            RECT_TREE_STUMP.width,
            RECT_TREE_STUMP.height
        };

        xAddTree(world, TREE_STUMP, temp);
    }
}

/// Load ponds 6 by 6 at their world coordinates.
static void xLoadPond6x6(World *world)
{
    xRectangle dest = 
    {
        posPonds[0].x,
        posPonds[0].y,
        64 * 6,
        64 * 5
    };

    xAddPond6x6(world, dest);
}

/// Load ground blocks at their world coordinates.
static void xLoadGroundBlock(World *world)
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

/// Load empty collider objects at their world coordinates.
static void xLoadScreenBoundary(World *world)
{
    // Left Margin
    xRectangle dest = {-1, 0, 7, GetScreenHeight()};
    xAddEmptyObject(world, dest);

    // Top Margin
    dest = (xRectangle){0, 63, GetScreenWidth(), 1};
    xAddEmptyObject(world, dest);

    // Right Margin
    dest = (xRectangle){GetScreenWidth() - 8, 0, 1, GetScreenHeight()};
    xAddEmptyObject(world, dest);

    // Bottom Margin
    dest = (xRectangle){0, GetScreenHeight() - 48, GetScreenWidth(), 1};
    xAddEmptyObject(world, dest);    
}

/// Load all elements of forest map. 
void xLoadForestMap(World *world)
{
    xLoadScreenBoundary(world);
    xLoadPond6x6(world);
    xLoadGroundBlock(world);
    xLoadTreesLarge1(world);
    xLoadTreesSmall1(world);
    xLoadMushrooms(world);
    xLoadRocks(world);
    xLoadTreesCut(world);
    xLoadTreesStump(world);
}
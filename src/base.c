#include "base.h"
#include "assets.h"
#include "sprites.h"
#include "animal.h"
#include "base_data.h"

/// Load all trees at their world coordinates.
static void xLoadTrees(World *world)
{
    // Load large trees.
    for (int i=0; i<treesOakLargeCount; i++)
    {
        xRectangle temp =
        {
            treesOakLarge[i].x,
            treesOakLarge[i].y,
            SRC_TREE_OAK_LARGE.width,
            SRC_TREE_OAK_LARGE.height
        };

        xAddTree(world, TREE_TYPE_OAK, TREE_STAGE_LARGE, temp);
    }
}

/// Load house at world coordinates.
static void xLoadHouse(World *world)
{
    xRectangle temp =
    {
        house[0].x,
        house[0].y,
        SRC_HOUSE_WOOD_CABIN.width,
        SRC_HOUSE_WOOD_CABIN.height
    };

    xAddHouse(world, HOUSE_TYPE_WOOD_CABIN, temp);
}

/// Load light posts at world coordinates.
// static void xLoadLightPost(World *world)
// {
//     xRectangle dest =
//     {
//         64 * 6 + 16,
//         64 * 4,
//         SRC_LIGHT_POST.width,
//         SRC_LIGHT_POST.height
//     };

//     xAddLightPost(world, dest);
// }

/// Load rocks at world coordinates.
// static void xLoadRocks(World *world)
// {
//     xRectangle dest =
//     {
//         64*2 - 26,
//         64*6 - 21,
//         SRC_ROCK_SMALL.width,
//         SRC_ROCK_SMALL.height
//     };

//     xAddRock(world, ROCK_SMALL, dest);
// }

// /// Load animals at world coordinates.
// static void xLoadAnimals(AnimalManager *manager)
// {
//     xRectangle dest =
//     {
//         464,
//         400-128,
//         SRC_COW.width,
//         SRC_COW.height
//     };
//     xSpawnCow(manager, dest);

//     dest = (xRectangle)
//     {
//         764,
//         640,
//         SRC_SHEEP.width,
//         SRC_SHEEP.height
//     };
//     xSpawnSheep(manager, dest);

//     dest = (xRectangle)
//     {
//         640,
//         632,
//         SRC_PIG.width,
//         SRC_PIG.height
//     };
//     xSpawnPig(manager, dest);

//     dest = (xRectangle)
//     {
//         700,
//         600,
//         SRC_COW.width,
//         SRC_COW.height
//     };
//     xSpawnCow(manager, dest);

//     dest = (xRectangle)
//     {
//         400,
//         400,
//         SRC_CHICKEN.width,
//         SRC_CHICKEN.height
//     };
//     xSpawnChicken(manager, dest);

//     dest = (xRectangle)
//     {
//         464,
//         400,
//         SRC_CHICKEN.width,
//         SRC_CHICKEN.height
//     };
//     xSpawnChicken(manager, dest);

//     dest = (xRectangle)
//     {
//         600,
//         464,
//         SRC_CHICKEN.width,
//         SRC_CHICKEN.height
//     };
//     xSpawnChicken(manager, dest);

//     dest = (xRectangle)
//     {
//         650,
//         500,
//         SRC_CHICKEN.width,
//         SRC_CHICKEN.height
//     };
//     xSpawnChicken(manager, dest);
// }

// static void xHighGroundColliders(World *world, xRectangle const highGround[])
// {
//     // Top row
//     xRectangle collider =
//     {
//         highGround[0].x + 48,
//         highGround[0].y + 28,
//         highGround[0].width - 48,
//         highGround[0].height - 40,
//     };
//     xAddEmptyEntity(world, collider);

//     // Left column
//     collider = (xRectangle)
//     {
//         highGround[1].x + 28,
//         highGround[1].y - 16,
//         highGround[1].width - 44,
//         highGround[1].height - 32,
//     };
//     xAddEmptyEntity(world, collider);

//     // Bottom row
//     collider = (xRectangle)
//     {
//         highGround[2].x - 16,
//         highGround[2].y + 16,
//         highGround[2].width + 16,
//         highGround[2].height - 48,
//     };
//     xAddEmptyEntity(world, collider);
// }

static void xLoadGrass(World *world)
{
    // Grass Variant 1
    for (int i = 0; i < grass1Count; i++)
    {
        xRectangle temp =
        {
            grass1[i].x,
            grass1[i].y,
            SRC_GRASS_1[0].width,
            SRC_GRASS_1[0].height
        };

        xAddGrass(world, GRASS_VAR_1, temp);
    }

    // Grass Variant 2
    for (int i = 0; i < grass2Count; i++)
    {
        xRectangle temp =
        {
            grass2[i].x,
            grass2[i].y,
            SRC_GRASS_2[0].width,
            SRC_GRASS_2[0].height
        };

        xAddGrass(world, GRASS_VAR_2, temp);
    }

    // Grass Variant 3
    for (int i = 0; i < grass3Count; i++)
    {
        xRectangle temp =
        {
            grass3[i].x,
            grass3[i].y,
            SRC_GRASS_3[0].width,
            SRC_GRASS_3[0].height
        };

        xAddGrass(world, GRASS_VAR_3, temp);
    }
}

static void xLoadLightPosts(World *world)
{
    for (int i = 0; i < lightPostsCount; i++)
    {
        xRectangle temp =
        {
            lightPosts[i].x,
            lightPosts[i].y,
            SRC_LIGHT_POST_WOOD_1[0].width,
            SRC_LIGHT_POST_WOOD_1[0].height
        };

        xAddLightPost(world, temp);
    }
}

static void xLoadUpperLayers(World *world)
{
    for (int i = 0; i < upperLayerCount; i++)
    {
        xRectangle temp =
        {
            upperLayer[i].x,
            upperLayer[i].y,
            64,
            64,
        };

        xAddUpperLayerColliders(world, upperLayer[i].index, temp);
    }
}

static void xLoadStairs(World *world)
{
    for (int i = 0; i < upperLayerStairsCount; i++)
    {
        xRectangle temp =
        {
            upperLayerStairs[i].x,
            upperLayerStairs[i].y,
            SRC_STAIRS_GROUND.width,
            SRC_STAIRS_GROUND.height
        };

        xAddStairs(world, temp);
    }
}

static void xLoadHedges(World *world)
{
    xRectangle temp = {0, 0, 64, 64};
    
    xAddHedge(world, HEDGE_HOR_LEFT, temp);

    for (int i = 64; i < hedgeContinuous->width - 64; i += 64)
    {
        temp = (xRectangle)
        {
            i,
            0,
            64,
            64
        };

        xAddHedge(world, HEDGE_HOR_CENTER, temp);
    }

    temp = (xRectangle)
    {
        temp.x + 64,
        temp.y,
        temp.width,
        temp.height
    };

    xAddHedge(world, HEDGE_HOR_RIGHT, temp);

    temp = (xRectangle)
    {
        0,
        64,
        temp.width,
        temp.height
    };

    xAddHedge(world, HEDGE_SINGLE, temp);

    temp = (xRectangle)
    {
        0,
        128,
        temp.width,
        temp.height
    };

    xAddHedge(world, HEDGE_SINGLE, temp);
}

static void xLoadWildflowers(World *world)
{
    xRectangle temp = {0};
    WildflowerVariant variant = WF_VAR_YELLOW_1;

    for (int i = 0; i < wildflower1Count; i++)
    {
        temp = (xRectangle)
        {
            wildflower1[i].x,
            wildflower1[i].y,
            SRC_WF_YELLOW_1[0].width,
            SRC_WF_YELLOW_1[0].height
        };

        xAddWildflowers(world, variant, temp);
    }

    variant = WF_VAR_YELLOW_2;

    for (int i = 0; i < wildflower2Count; i++)
    {
        temp = (xRectangle)
        {
            wildflower2[i].x,
            wildflower2[i].y,
            SRC_WF_YELLOW_2[0].width,
            SRC_WF_YELLOW_2[0].height
        };

        xAddWildflowers(world, variant, temp);
    }

    variant = WF_VAR_YELLOW_3;

    for (int i = 0; i < wildflower3Count; i++)
    {
        temp = (xRectangle)
        {
            wildflower3[i].x,
            wildflower3[i].y,
            SRC_WF_YELLOW_3[0].width,
            SRC_WF_YELLOW_3[0].height
        };

        xAddWildflowers(world, variant, temp);
    }
}

static void xLoadCliffColliders(World *world)
{
    for (int i = 0; i < cliffCollidersCount; i++)
    {
        xRectangle temp = 
        {
            cliffColliders[i].x,
            cliffColliders[i].y,
            64,
            64
        };
        xAddCliffCollider(world, cliffColliders[i].index, temp);
    }
}

static void xLoadCliffStairs(World *world)
{
    for (int i = 0; i < cliffStairsCount; i++)
    {
        xRectangle temp =
        {
            cliffStairs[i].x,
            cliffStairs[i].y,
            SRC_CLIFF_STAIRS_WOOD.width,
            SRC_CLIFF_STAIRS_WOOD.height
        };
        xAddCliffStairs(world, temp);
    }
}

static void xLoadFarmlands(World *world)
{
    xRectangle temp = {0};

    for (int i = 0; i < farmlandsDryCount; i++)
    {
        temp = (xRectangle)
        {
            farmlandsDry[i].x,
            farmlandsDry[i].y,
            64,
            64
        };

        xAddFarmland(world, farmlandsDry[i].index, temp);
    }
}

void xLoadBaseMap(World *world, AnimalManager *manager)
{
    xLoadFarmlands(world);
    xLoadCliffColliders(world);
    xLoadCliffStairs(world);
    xLoadWildflowers(world);
    xLoadHedges(world);
    xLoadStairs(world);
    xLoadUpperLayers(world);
    xLoadLightPosts(world);
    xLoadTrees(world);
    xLoadGrass(world);
    xLoadHouse(world);
}
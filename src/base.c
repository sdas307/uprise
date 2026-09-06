#include "base.h"
#include "assets.h"
#include "sprites.h"
#include "animal.h"
#include "base_data.h"

/// Load all trees at their world coordinates.
static void xLoadTrees(World *world)
{
    // Load large oak trees.
    for (int i = 0; i < treesOakLargeCount; i++)
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

    // Load large birch trees.
    for (int i = 0; i < treesBirchLargeCount; i++)
    {
        xRectangle temp =
        {
            treesBirchLarge[i].x,
            treesBirchLarge[i].y,
            SRC_TREE_BIRCH_LARGE.width,
            SRC_TREE_BIRCH_LARGE.height
        };

        xAddTree(world, TREE_TYPE_BIRCH, TREE_STAGE_LARGE, temp);
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

/// Load animals at world coordinates.
static void xLoadAnimals(AnimalManager *manager)
{
    xRectangle dest =
    {
        1000,
        1000,
        SRC_COW.width,
        SRC_COW.height
    };
    xSpawnCow(manager, dest);

    dest = (xRectangle)
    {
        1000,
        1000,
        SRC_SHEEP.width,
        SRC_SHEEP.height
    };
    xSpawnSheep(manager, dest);

    dest = (xRectangle)
    {
        1000,
        1000,
        SRC_PIG.width,
        SRC_PIG.height
    };
    xSpawnPig(manager, dest);

    dest = (xRectangle)
    {
        1000,
        1000,
        SRC_COW.width,
        SRC_COW.height
    };
    xSpawnCow(manager, dest);

    dest = (xRectangle)
    {
        1000,
        1000,
        SRC_CHICKEN.width,
        SRC_CHICKEN.height
    };
    xSpawnChicken(manager, dest);

    dest = (xRectangle)
    {
        1000,
        1000,
        SRC_CHICKEN.width,
        SRC_CHICKEN.height
    };
    xSpawnChicken(manager, dest);

    dest = (xRectangle)
    {
        1000,
        1000,
        SRC_CHICKEN.width,
        SRC_CHICKEN.height
    };
    xSpawnChicken(manager, dest);

    dest = (xRectangle)
    {
        1000,
        1000,
        SRC_CHICKEN.width,
        SRC_CHICKEN.height
    };
    xSpawnChicken(manager, dest);
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

// static void xLoadWildflowers(World *world)
// {
//     xRectangle temp = {0};
//     WildflowerVariant variant = WF_VAR_YELLOW_1;

//     for (int i = 0; i < wildflower1Count; i++)
//     {
//         temp = (xRectangle)
//         {
//             wildflower1[i].x,
//             wildflower1[i].y,
//             SRC_WILDFLOWER[0].width,
//             SRC_WILDFLOWER[0].height
//         };

//         xAddWildflowers(world, variant, temp);
//     }

//     variant = WF_VAR_YELLOW_2;

//     for (int i = 0; i < wildflower2Count; i++)
//     {
//         temp = (xRectangle)
//         {
//             wildflower2[i].x,
//             wildflower2[i].y,
//             SRC_WILDFLOWER[0].width,
//             SRC_WILDFLOWER[0].height
//         };

//         xAddWildflowers(world, variant, temp);
//     }

//     variant = WF_VAR_YELLOW_3;

//     for (int i = 0; i < wildflower3Count; i++)
//     {
//         temp = (xRectangle)
//         {
//             wildflower3[i].x,
//             wildflower3[i].y,
//             SRC_WILDFLOWER[0].width,
//             SRC_WILDFLOWER[0].height
//         };

//         xAddWildflowers(world, variant, temp);
//     }
// }

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

static void xLoadCliffStairsColliders(World *world)
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
        xAddCliffStairsCollider(world, temp);
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
    xLoadAnimals(manager);
    xLoadFarmlands(world);
    xLoadCliffColliders(world);
    xLoadCliffStairsColliders(world);
    // xLoadWildflowers(world);
    xLoadHedges(world);
    xLoadStairs(world);
    xLoadUpperLayers(world);
    xLoadLightPosts(world);
    xLoadTrees(world);
    // xLoadGrass(world);
    xLoadHouse(world);
}
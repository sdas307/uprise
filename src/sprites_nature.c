#include "sprites_nature.h"

const xRectangle SRC_CLIFF_STAIRS_WOOD = 
{
    24 * 64,
    6 * 64,
    64 * 3,
    64 * 3
};

const xRectangle SRC_FARMLAND_DRY[] =
{
    { 1 * 64, 22 * 64, 64, 64 },
    { 2 * 64, 22 * 64, 64, 64 },
    { 3 * 64, 22 * 64, 64, 64 },
    { 1 * 64, 23 * 64, 64, 64 },
    { 2 * 64, 23 * 64, 64, 64 },
    { 3 * 64, 23 * 64, 64, 64 },
    { 1 * 64, 24 * 64, 64, 64 },
    { 2 * 64, 24 * 64, 64, 64 },
    { 3 * 64, 24 * 64, 64, 64 }
};

const xRectangle SRC_FARMLAND_WET[] =
{
    { 8 * 64, 22 * 64, 64, 64 },
    { 9 * 64, 22 * 64, 64, 64 },
    { 10 * 64, 22 * 64, 64, 64 },
    { 8 * 64, 23 * 64, 64, 64 },
    { 9 * 64, 23 * 64, 64, 64 },
    { 10 * 64, 23 * 64, 64, 64 },
    { 8 * 64, 24 * 64, 64, 64 },
    { 9 * 64, 24 * 64, 64, 64 },
    { 10 * 64, 24 * 64, 64, 64 }
};

/* --------------- TERRAIN DECOR SPRITES --------------- */

// Contains 3 static grass variants.
const xRectangle SRC_GRASS[] =
{
    { 64 * 3, 64 * 0, 64, 64 },     // Grass Variant 1
    { 64 * 4, 64 * 0, 64, 64 },     // Grass Variant 2
    { 64 * 5, 64 * 0, 64, 64 }      // Grass Variant 3
};

/* --------------- --------------- --------------- */


/* --------------- TERRAIN SPRITES --------------- */

const xRectangle SRC_STAIRS_GROUND =
{
    64 * 22,
    64 * 0,
    64 * 2,
    64 * 2
};

const xRectangle SRC_STAIRS_STONE =
{
    64 * 22,
    64 * 5,
    64 * 2,
    64 * 2
};

const xRectangle SRC_HEDGE_VER_TOP =
{
    64 * 16,
    64 * 5,
    64,
    64
};

const xRectangle SRC_HEDGE_VER_CENTER =
{
    64 * 16,
    64 * 6,
    64,
    64
};

const xRectangle SRC_HEDGE_VER_BOTTOM =
{
    64 * 16,
    64 * 7,
    64,
    64
};

const xRectangle SRC_HEDGE_HOR_LEFT =
{
    64 * 17,
    64 * 5,
    64,
    64
};

const xRectangle SRC_HEDGE_HOR_CENTER =
{
    64 * 18,
    64 * 5,
    64,
    64
};

const xRectangle SRC_HEDGE_HOR_RIGHT =
{
    64 * 19,
    64 * 5,
    64,
    64
};

const xRectangle SRC_HEDGE_SINGLE =
{
    64 * 16,
    64 * 8,
    64,
    64
};

/* --------------- --------------- --------------- */


/* --------------- TREE SPRITES --------------- */

// BIRCH TREE --|
//              v

const xRectangle SRC_TREE_BIRCH_CUT =
{
    64 * 1,
    64 * 0,
    64 * 2,
    64 * 5
};

const xRectangle SRC_TREE_BIRCH_SMALL =
{
    64 * 5 + 15,
    64 * 5,
    64 * 2 - 34,
    64 * 2
};

const xRectangle SRC_TREE_BIRCH_MEDIUM =
{
    64 * 2,
    64 * 5,
    64 * 2,
    64 * 3
};

const xRectangle SRC_TREE_BIRCH_LARGE =
{
    64 * 3,
    64 * 0,
    64 * 2,
    64 * 5
};

const xRectangle SRC_TREE_BIRCH_LARGE_CHOPPED =
{
    64 * 4,
    64 * 0,
    64 * 2,
    64 * 5
};

// OAK TREE --|
//            v

const xRectangle SRC_TREE_OAK_CUT =
{
    64 * 8,
    64 * 0,
    64 * 4,
    64 * 5
};

const xRectangle SRC_TREE_OAK_SMALL =
{
    64 * 9,
    64 * 9,
    64 * 2,
    64 * 2
};

const xRectangle SRC_TREE_OAK_MEDIUM =
{
    64 * 9,
    64 * 5,
    64 * 2,
    64 * 3
};

const xRectangle SRC_TREE_OAK_LARGE =
{
    64 * 12,
    64 * 0,
    64 * 4,
    64 * 5
};

const xRectangle SRC_TREE_OAK_LARGE_CHOPPED =
{
    64 * 13,
    64 * 0,
    64 * 4,
    64 * 5
};

// SPRUCE TREE --|
//               v

const xRectangle SRC_TREE_SPRUCE_CUT =
{
    64 * 0,
    64 * 2,
    64,
    64
};

const xRectangle SRC_TREE_SPRUCE_SMALL =
{
    64 * 5 + 15,
    64 * 5,
    64 * 2 - 34,
    64 * 2
};

const xRectangle SRC_TREE_SPRUCE_MEDIUM =
{
    64 * 7,
    64 * 0,
    64 * 4,
    64 * 5
};

const xRectangle SRC_TREE_SPRUCE_LARGE =
{
    64 * 7,
    64 * 0,
    64 * 4,
    64 * 5
};

const xRectangle SRC_TREE_LOG =
{
    0,
    64 * 7,
    64 * 2,
    64
};

/* --------------- --------------- --------------- */


/* --------------- ROCK/STONE SPRITES --------------- */

// ROCKS --|
//         v

const xRectangle SRC_ROCK_SMALL = 
{
    64 * 1 + 8,
    64 * 2 + 20,
    64 - 24,
    64 - 36
};

const xRectangle SRC_ROCK_LARGE = 
{
    64 * 2,
    64 * 2 + 2,
    64 - 1,
    64 - 4
};

// STONE --|
//         v

const xRectangle SRC_STONE_SMALL =
{
    64 * 2,
    64 * 3,
    64,
    64
};

const xRectangle SRC_STONE_MEDIUM =
{
    64 * 1,
    64 * 3,
    64,
    64
};

const xRectangle SRC_STONE_LARGE = 
{
    64 * 0,
    64 * 3,
    64,
    64
};

/* --------------- --------------- --------------- */


/* --------------- FLOWER/MUSHROOM SPRITES --------------- */

// MUSHROOM --|
//            v

const xRectangle SRC_MUSHROOM_RED = 
{
    64 * 0,
    64 * 22,
    64,
    64
};

const xRectangle SRC_MUSHROOM_BLUE = 
{
    64 * 14,
    64 * 22,
    64,
    64
};

const xRectangle SRC_MUSHROOM_NAKED = 
{
    64 * 21,
    64 * 23,
    64,
    64
};

// RED FLOWERS --|
//               v

const xRectangle SRC_FLOWER_RED_1 =
{
    64 * 3,
    64 * 7,
    64,
    64
};

const xRectangle SRC_FLOWER_RED_2 =
{
    64 * 3,
    64 * 8,
    64,
    64
};

const xRectangle SRC_FLOWER_RED_3 =
{
    64 * 3,
    64 * 9,
    64,
    64
};

const xRectangle SRC_FLOWER_RED_4 =
{
    64 * 3,
    64 * 10,
    64,
    64
};

// YELLOW FLOWERS --|
//                  v

const xRectangle SRC_FLOWER_YELLOW_1 =
{
    64 * 4,
    64 * 7,
    64,
    64
};

const xRectangle SRC_FLOWER_YELLOW_2 =
{
    64 * 4,
    64 * 8,
    64,
    64
};

const xRectangle SRC_FLOWER_YELLOW_3 =
{
    64 * 4,
    64 * 9,
    64,
    64
};

const xRectangle SRC_FLOWER_YELLOW_4 =
{
    64 * 4,
    64 * 10,
    64,
    64
};

/* --------------- --------------- --------------- */
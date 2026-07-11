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

#define ARRAY_COUNT(x) (sizeof(x) / sizeof((x)[0]))

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

void xLoadTreesLarge(World *world)
{
    for (int i=0; i<ARRAY_COUNT(largeTrees); i++)
    {
        xAddTree(world, TREE_LARGE, largeTrees[i]);
    }
}

void xLoadTreesSmall(World *world)
{
    for (int i=0; i<ARRAY_COUNT(smallTrees); i++)
    {
        xAddTree(world, TREE_SMALL, smallTrees[i]);
    }
}

void xLoadHouse(World *world)
{
    xAddHouse(world, house);
}
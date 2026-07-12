#include "base.h"
#include "assets.h"
#include <stdio.h>


bool xLoadBaseConfig(BaseConfig *config)
{
    FILE *file = fopen("config/base.cfg", "r");

    if (file == NULL)
    {
        perror("Failed to open base.cfg");
        return false;
    }

    int temp;

    if ((fscanf(file, " largetree1x = %f", &config->largeTrees[config->largeTreesCount++].x) != 1) ||
        (fscanf(file, " largetree2x = %f", &config->largeTrees[config->largeTreesCount++].x) != 1) ||
        (fscanf(file, " largetree3x = %f", &config->largeTrees[config->largeTreesCount++].x) != 1) ||
        (fscanf(file, " largetree4x = %f", &config->largeTrees[config->largeTreesCount++].x) != 1) ||
        (fscanf(file, " largetreesY = %f", &temp) != 1))
    {
        fclose(file);
        return false;
    }
    
    config->largeTrees[0].y = temp;
    printf("\n\nlargetree1x: %f\n\n", config->largeTrees[0].x);

    fclose(file);
    return true;
}

/* ---------- Destination Rectangles ----------*/

// static const xRectangle largeTrees[] =
// {
//     { 64*5 + 15, -32, 64 * 3 - 27, 64 * 4 },
//     { 64*6 +  8, -32, 64 * 3 - 27, 64 * 4 },
//     { 64*9 + 16, -32, 64 * 3 - 27, 64 * 4 },
//     { 64*10 + 12, -32, 64 * 3 - 27, 64 * 4 }
    
// };

xRectangle largeTrees[MAX_TREES];

void xBaseInit(BaseConfig *config)
{
    xLoadBaseConfig(config);

    for (int i=0; i < config->largeTreesCount; i++)
    {
        largeTrees[i].x = config->largeTrees[i].x;
        largeTrees[i].y = config->largeTrees[0].y;

        largeTrees[i].width = SPRITE_TREE_LARGE.width;
        largeTrees[i].height = SPRITE_TREE_LARGE.height;
    }
}

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


void xLoadTreesLarge(World *world)
{
    for (int i=0; i<ARRAY_COUNT(largeTrees); i++)
    {
        printf("\n\n%f, %f, %f, %f\n\n",
        largeTrees[i].x, largeTrees[i].y,
        largeTrees[i].width, largeTrees[i].height);

        xAddTree(world, TREE_LARGE, largeTrees[0]);
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
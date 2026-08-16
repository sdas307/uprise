#include "world.h"
#include "animal.h"
#include "config.h"
#include "assets.h"
#include "entities.h"
#include "base.h"
#include "forest.h"

void xInitWorld(World *world)
{
    // Initialize terrain
    world->terrain.texture = LoadTexture(PATH_START_BASE);
    SetTextureFilter(world->terrain.texture, TEXTURE_FILTER_POINT);

    // world->terrain.source = (xRectangle){0, 0, 1024, 832};
    // world->terrain.dest = (xRectangle){0, 0, 1024, 832};

    world->terrain.source = (xRectangle){0, 0, 3072, 1664};
    world->terrain.dest = (xRectangle){0, 0, 3072, 1664};

    // // Initialize world objects sprite sheet
    // world->spriteSheet = LoadTexture(PATH_SPRITE_SHEET);
    // SetTextureFilter(world->spriteSheet, TEXTURE_FILTER_POINT);
 
    // Spritesheets
    for (int i = 0; i < path_spritesheets_size; i++)
    {
        world->spritesheets[i] = LoadTexture(PATH_SPRITESHEETS[i]);
        SetTextureFilter(world->spritesheets[i], TEXTURE_FILTER_POINT);
    }

    world->entityCount = 0;
}

void xUnloadWorld(World *world)
{
    UnloadTexture(world->terrain.texture);

    for (int i = 0; i < path_spritesheets_size; i++)
    {
        UnloadTexture(world->spritesheets[i]);
    }
}

void xLoadWorld(World *world, AnimalManager *manager)
{
    xLoadBaseMap(world, manager);

    // xLoadForestMap(world);
}
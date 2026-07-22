#include "world.h"
#include "config.h"
#include "assets.h"
#include "world_objects.h"
#include "base.h"
#include "forest.h"

/* ---------- Implementation ---------- */

void xInitWorld(World *world)
{
    // Initialize terrain
    world->terrain.texture = LoadTexture(PATH_FOREST);
    SetTextureFilter(world->terrain.texture, TEXTURE_FILTER_POINT);

    world->terrain.source = (xRectangle){0, 0, 1024, 832};
    world->terrain.dest = (xRectangle){0, 0, 1024, 832};

    // Initialize world objects sprite sheet
    world->spriteSheet = LoadTexture(PATH_SPRITE_SHEET);
    SetTextureFilter(world->spriteSheet, TEXTURE_FILTER_POINT);

    world->entityCount = 0;
}

void xUnloadWorld(World *world)
{
    UnloadTexture(world->terrain.texture);
    UnloadTexture(world->spriteSheet);
}

void xLoadWorld(World *world, AnimalManager *manager)
{
    // xLoadBaseMap(world, manager);

    xLoadForestMap(world);
}
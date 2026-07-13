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

    world->objectCount = 0;
}

void xUnloadWorld(World *world)
{
    UnloadTexture(world->terrain.texture);
    UnloadTexture(world->spriteSheet);
}

void xLoadWorld(World *world, AnimalManager *manager)
{
    // xLoadTreesLarge(world);

    // xLoadHouse(world);

    // xLoadTreesSmall(world);

    // xAddLightPost(world, (xRectangle){64*6 + 16, 64*4, SPRITE_LIGHT_POST.width, SPRITE_LIGHT_POST.height});

    // xAddRock(world, ROCK_SMALL, (xRectangle){64*2 - 26, 64*6 - 21, SPRITE_ROCK_SMALL.width, SPRITE_ROCK_SMALL.height });

    // xSpawnCow(manager, (xRectangle){464, 400-128, SPRITE_COW.width, SPRITE_COW.height});

    // xSpawnChicken(manager, (xRectangle){400, 400, SPRITE_CHICKEN.width, SPRITE_CHICKEN.height});

    xAddMushroom(world, (xRectangle){400, 400, SPRITE_MUSHROOM.width, SPRITE_MUSHROOM.height});
    xAddMushroom(world, (xRectangle){464, 400, SPRITE_MUSHROOM.width, SPRITE_MUSHROOM.height});
    xAddMushroom(world, (xRectangle){464 + 64, 400, SPRITE_MUSHROOM.width, SPRITE_MUSHROOM.height});
}
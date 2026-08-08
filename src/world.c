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
    world->terrain.texture = LoadTexture(PATH_BASE);
    SetTextureFilter(world->terrain.texture, TEXTURE_FILTER_POINT);

    // world->terrain.source = (xRectangle){0, 0, 1024, 832};
    // world->terrain.dest = (xRectangle){0, 0, 1024, 832};

    world->terrain.source = (xRectangle){0, 0,3072, 1664};
    world->terrain.dest = (xRectangle){0, 0, 3072, 1664};

    // // Initialize world objects sprite sheet
    // world->spriteSheet = LoadTexture(PATH_SPRITE_SHEET);
    // SetTextureFilter(world->spriteSheet, TEXTURE_FILTER_POINT);

    // House spritesheet
    world->houseWood_spriteSheet = LoadTexture(PATH_HOUSE_WOOD_SPRITESHEET);

    // Nature spritesheets
    world->trees_spriteSheet = LoadTexture(PATH_TREES_SPRITESHEET);
    world->cliffs_spriteSheet = LoadTexture(PATH_CLIFFS_SPRITESHEET);
    world->cropFruits_spriteSheet = LoadTexture(PATH_CROPS_FRUITS_SPRITESHEET);
    world->flowersMushrooms_spriteSheet = LoadTexture(PATH_FLOWER_MUSHROOMS_SPRITESHEET);
    world->grassWildflowers_spriteSheet = LoadTexture(PATH_GRASS_WILDFLOWERS_SPRITESHEET);
    world->grasslands_spriteSheet = LoadTexture(PATH_GRASSLANDS_SPRITESHEET);
    world->water_spriteSheet = LoadTexture(PATH_WATER_SPRITESHEET);
    world->waterfall_spriteSheet = LoadTexture(PATH_WATERFALL_SPRITESHEET);

    // Structure spritesheets
    world->fencePosts_spriteSheet = LoadTexture(PATH_FENCE_POSTS_SPRITESHEET);
    world->bridgesWalls_spriteSheet = LoadTexture(PATH_BRIDGE_WALLS_SPRITESHEET);

    // Cave spritesheets
    world->cave_spriteSheet = LoadTexture(PATH_CAVE_SPRITESHEET);

    // Weather spritesheets
    world->weatherEffects_spriteSheet = LoadTexture(PATH_WEATHER_SPRITESHEET);

    world->entityCount = 0;
}

void xUnloadWorld(World *world)
{
    UnloadTexture(world->terrain.texture);

    // House spritesheets
    UnloadTexture(world->houseWood_spriteSheet);

    // Nature spritesheets
    UnloadTexture(world->trees_spriteSheet);
    UnloadTexture(world->cliffs_spriteSheet);
    UnloadTexture(world->cropFruits_spriteSheet);
    UnloadTexture(world->flowersMushrooms_spriteSheet);
    UnloadTexture(world->grassWildflowers_spriteSheet);
    UnloadTexture(world->grasslands_spriteSheet);
    UnloadTexture(world->water_spriteSheet);
    UnloadTexture(world->waterfall_spriteSheet);

    // Structure spritesheets
    UnloadTexture(world->fencePosts_spriteSheet);
    UnloadTexture(world->bridgesWalls_spriteSheet);

    // Cave spritesheets
    UnloadTexture(world->cave_spriteSheet);

    // Weather spritesheets
    UnloadTexture(world->weatherEffects_spriteSheet);
}

void xLoadWorld(World *world, AnimalManager *manager)
{
    xLoadBaseMap(world, manager);

    // xLoadForestMap(world);
}
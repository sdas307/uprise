#include "world.h"
#include "animal.h"
#include "config.h"
#include "assets.h"
#include "sprites_nature.h"
#include "entities.h"
#include "base.h"

void xInitWorld(World *world)
{
    // Initialize terrain
    world->terrain.texture = LoadTexture(PATH_START_BASE);
    SetTextureFilter(world->terrain.texture, TEXTURE_FILTER_POINT);

    const int baseMapWidth = SCREEN_WIDTH * 3;
    const int baseMapHeight = SCREEN_HEIGHT * 2;

    world->terrain.source = (xRectangle){0, 0, baseMapWidth, baseMapHeight};
    world->terrain.dest = (xRectangle){0, 0, baseMapWidth, baseMapHeight};
 
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
}

void xUpdateWorld(World *world, float dt)
{
    for (int i = 0; i < world->entityCount; i++)
    {
        Entity *entity = &world->entities[i];

        // if ((entity->type != TREE) && (entity->type != FARMLAND))
        //     continue;
        
        switch (entity->id)
        {
        case ENTITY_TREE_OAK_CUT:
            entity->gameObject.source = SRC_TREE_OAK_CUT;
            entity->gameObject.fadeable = false;
        break;

        case ENTITY_TREE_BIRCH_CUT:
            entity->gameObject.source = SRC_TREE_BIRCH_CUT;
            entity->gameObject.fadeable = false;
        break;
        
        case ENTITY_FARMLAND_WET:
            entity->gameObject.source = SRC_FARMLAND_WET[4];
        break;
        }
    }
}
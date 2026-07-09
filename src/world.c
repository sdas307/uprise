#include "world.h"
#include "config.h"
#include "assets.h"

/* ---------- Signatures ---------- */

static void xAddObject(World *world, xRectangle source, xRectangle dest, xRectangle collider);

static void xAddStone(World *world, StoneType type, xRectangle dest);

static void xAddTree(World *world, TreeStage stage, xRectangle dest);

static void xAddHouse(World *world, xRectangle dest);

static void xAddLightPost(World *world, xRectangle dest);

static void xAddRock(World *world, RockType type, xRectangle dest);


/* ---------- Implementation ---------- */

void xInitWorld(World *world)
{
    // Initialize terrain
    world->terrain.texture = LoadTexture(PATH_TERRAIN);
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

void xLoadWorld(World *world)
{
    xAddTree(world, TREE_LARGE, (xRectangle){64*5 + 15, -32, SPRITE_TREE_LARGE.width, SPRITE_TREE_LARGE.height});
    xAddTree(world, TREE_LARGE, (xRectangle){64*6 + 8, -32, SPRITE_TREE_LARGE.width, SPRITE_TREE_LARGE.height});
    xAddTree(world, TREE_LARGE, (xRectangle){64*9 + 16, - 32, SPRITE_TREE_LARGE.width, SPRITE_TREE_LARGE.height});
    xAddTree(world, TREE_LARGE, (xRectangle){64*10 + 12, -32, SPRITE_TREE_LARGE.width, SPRITE_TREE_LARGE.height});

    xAddHouse(world, (xRectangle){64*2 - 12, -58, SPRITE_HOUSE.width, SPRITE_HOUSE.height});

    xAddTree(world, TREE_SMALL, (xRectangle){64 - 9, 64*4 + 20, SPRITE_TREE_SMALL.width, SPRITE_TREE_SMALL.height});

    xAddLightPost(world, (xRectangle){64*6 + 16, 64*4, SPRITE_LIGHT_POST.width, SPRITE_LIGHT_POST.height});

    xAddRock(world, ROCK_SMALL, (xRectangle){64*2 - 26, 64*6 - 21, SPRITE_ROCK_SMALL.width, SPRITE_ROCK_SMALL.height });
}

static void xAddObject(World *world, xRectangle source, xRectangle dest, xRectangle collider)
{
    if (world->objectCount >= MAX_OBJECTS)
        return;

    xGameObject *object = &world->objects[world->objectCount++];

    object->texture = world->spriteSheet;

    object->source = source;
    object->dest = dest;

    object->collider = collider;

    object->depth = collider.y + collider.height;

    object->flip = false;
    object->active = true;
}

static void xAddHouse(World *world, xRectangle dest)
{
    xRectangle source = SPRITE_HOUSE;
    xRectangle collider =
    {
        dest.x + 12,
        dest.y + 64*6 - 68,
        dest.width - 12,
        128
    };

    xAddObject(world, source, dest, collider);
}

static void xAddLightPost(World *world, xRectangle dest)
{
    xRectangle source = SPRITE_LIGHT_POST;
    xRectangle collider =
    {
        dest.x + 18,
        dest.y + dest.height - 20,
        dest.width - 30,
        20
    };
    
    xAddObject(world, source, dest, collider);
}

static void xAddRock(World *world, RockType type, xRectangle dest)
{
    xRectangle source;
    xRectangle collider;

    switch (type)
    {
        case ROCK_SMALL:
        source = SPRITE_ROCK_SMALL;

        collider = (xRectangle){
            dest.x + 8,
            dest.y + dest.height - 18,
            dest.width - 10,
            16
        };
        break;

        case ROCK_LARGE:
        source = SPRITE_ROCK_LARGE;

        collider = (xRectangle){
            dest.x,
            dest.y + dest.height - 20,
            dest.width,
            20
        };
        break;
    }

    xAddObject(world, source, dest, collider);

}

static void xAddStone(World *world, StoneType type, xRectangle dest)
{
    xRectangle source;
    xRectangle collider;

    switch (type)
    {
    case STONE_SMALL:
        source = SPRITE_STONE_SMALL;

        collider = (xRectangle){
            dest.x + 12,
            dest.y + 36,
            38,
            20,
        };
        break;

    case STONE_MEDIUM:
        source = SPRITE_STONE_MEDIUM;

        collider = (xRectangle){
            dest.x + 14,
            dest.y + 36,
            42,
            20,
        };
        break;

    case STONE_LARGE:
        source = SPRITE_STONE_LARGE;

        collider = (xRectangle){
            dest.x + 8,
            dest.y + 36,
            50,
            20,
        };
        break;
    }

    xAddObject(world, source, dest, collider);
}

static void xAddTree(World *world, TreeStage stage, xRectangle dest)
{
    xRectangle source;
    xRectangle collider;

    switch (stage)
    {
    case TREE_STUMP:
        source = (xRectangle){64 * 0, 64 * 8, 64, 64};
        break;

    case TREE_CUT:
        source = SPRITE_TREE_CUT;

        collider = (xRectangle){
            dest.x + 4,
            dest.y + 38,
            56,
            20,
        };
        break;

    case TREE_SMALL:
        source = SPRITE_TREE_SMALL;

        collider = (xRectangle){
            dest.x + dest.width / 2 - 15,
            dest.y + 90,
            28,
            20,
        };
        break;

    case TREE_LARGE:
        source = SPRITE_TREE_LARGE;

        collider = (xRectangle){
            dest.x + dest.width/2 - 26,
            dest.y + 206,
            58,
            20,
        };
        break;
    }

    xAddObject(world, source, dest, collider);
}
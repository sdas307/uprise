#include "world.h"
#include "config.h"

/* ---------- Signatures ---------- */

static void xAddObject(World *world, xRectangle source, xRectangle dest, xRectangle collider);

static void xAddStone(World *world, StoneType type, xRectangle dest);

static void xAddTree(World *world, TreeStage stage, xRectangle dest);

static void xAddHouse(World *world, xRectangle dest);

static void xAddLightPost(World *world, xRectangle dest);


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
    xAddTree(world, TREE_LARGE, (xRectangle){64*5 - 1, -32, 64 * 3, 64 * 4});
    xAddTree(world, TREE_LARGE, (xRectangle){64*6 - 8, -32, 64 * 3, 64 * 4});
    xAddTree(world, TREE_LARGE, (xRectangle){64*9, -32, 64 * 3, 64 * 4});
    xAddTree(world, TREE_LARGE, (xRectangle){64*10 - 4, -32, 64 * 3, 64 * 4});

    xAddHouse(world, (xRectangle){64*2 - 12, -120, 64 * 5, 64 * 8});

    xAddTree(world, TREE_SMALL, (xRectangle){40, 64*4 + 20, 64 * 2, 64 * 2});

    xAddLightPost(world, (xRectangle){64*6, 64*3 + 4, 64 * 1, 64 * 3});
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
    xRectangle source = (xRectangle){64 * 15, 64 * 0, 64 * 5, 64 * 8};
    xRectangle collider =
    {
        dest.x + 8,
        dest.y + 64*6 - 6,
        dest.width - 50,
        128
    };

    xAddObject(world, source, dest, collider);
}

static void xAddLightPost(World *world, xRectangle dest)
{
    xRectangle source = (xRectangle){64 * 4, 64 * 4, 64 * 1, 64 * 3};
    xRectangle collider =
    {
        dest.x + 16,
        dest.y + 166,
        dest.width - 30,
        20
    };
    
    xAddObject(world, source, dest, collider);
}

static void xAddStone(World *world, StoneType type, xRectangle dest)
{
    xRectangle source;
    xRectangle collider;

    switch (type)
    {
    case STONE_SMALL:
        source = (xRectangle){64 * 2, 64 * 3, 64, 64};

        collider = (xRectangle){
            dest.x + 12,
            dest.y + 36,
            38,
            20,
        };
        break;

    case STONE_MEDIUM:
        source = (xRectangle){64 * 1, 64 * 3, 64, 64};

        collider = (xRectangle){
            dest.x + 14,
            dest.y + 36,
            42,
            20,
        };
        break;

    case STONE_LARGE:
        source = (xRectangle){64 * 0, 64 * 3, 64, 64};

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
        source = (xRectangle){64 * 0, 64 * 2, 64, 64};

        collider = (xRectangle){
            dest.x + 4,
            dest.y + 38,
            56,
            20,
        };
        break;

    case TREE_SMALL:
        source = (xRectangle){64 * 5, 64 * 5, 64 * 2, 64 * 2};

        collider = (xRectangle){
            dest.x + dest.width / 2 - 15,
            dest.y + 90,
            20,
            20,
        };
        break;

    case TREE_LARGE:
        source = (xRectangle){64 * 8, 64 * 1, 64 * 3, 64 * 4};

        collider = (xRectangle){
            dest.x + 74,
            dest.y + 206,
            52,
            20,
        };
        break;
    }

    xAddObject(world, source, dest, collider);
}
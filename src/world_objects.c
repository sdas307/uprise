#include "world_objects.h"
#include "assets.h"

static void xAddObject(World *world, xRectangle source, xRectangle dest, xRectangle collider)
{
    if (world->objectCount >= MAX_OBJECTS)
        return;

    xGameObject *object = &world->objects[world->objectCount++];

    object->texture = world->spriteSheet;

    object->source = source;
    object->dest = dest;

    object->type = OBJECT_WORLD_OBJECT;

    object->collider = collider;

    object->depth = collider.y + collider.height;

    object->flip = false;
    object->active = true;
}

void xAddHouse(World *world, xRectangle dest)
{
    xRectangle source = SPRITE_HOUSE;
    xRectangle collider =
    {
        dest.x,
        dest.y + 64*6 - 68,
        dest.width,
        128
    };

    xAddObject(world, source, dest, collider);
}

void xAddLightPost(World *world, xRectangle dest)
{
    xRectangle source = SPRITE_LIGHT_POST;
    xRectangle collider =
    {
        dest.x,
        dest.y + dest.height - 20,
        dest.width,
        20
    };
    
    xAddObject(world, source, dest, collider);
}

void xAddRock(World *world, RockType type, xRectangle dest)
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

void xAddStone(World *world, StoneType type, xRectangle dest)
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

void xAddTree(World *world, TreeStage stage, xRectangle dest)
{
    xRectangle source;
    xRectangle collider;

    switch (stage)
    {
    case TREE_STUMP:
        source = SPRITE_TREE_STUMP;
        
        collider = (xRectangle){
            dest.x,
            dest.y + dest.height - 16,
            dest.width - 2,
            8
        };
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

void xAddMushroom(World *world, xRectangle dest)
{
    xRectangle source;
    xRectangle collider;

    source = SPRITE_MUSHROOM;

    collider = (xRectangle)
    {
        dest.x + 4,
        dest.y + 20,
        dest.width - 8,
        8
    };

    xAddObject(world, source, dest, collider);
}
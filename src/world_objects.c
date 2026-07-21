#include "world_objects.h"
#include "sprites.h"

static void xAddObject(World *world, EntityID id, xRectangle source, xRectangle dest, xRectangle collider)
{
    if (world->entityCount >= MAX_OBJECTS)
        return;

    xGameObject *object = &world->entities[world->entityCount++].gameObject;

    object->texture = world->spriteSheet;

    object->source = source;
    object->dest = dest;

    object->type = OBJECT_ENTITY;

    object->collider = collider;

    object->depth = collider.y + collider.height;

    object->flip = false;
    object->active = true;
}

void xAddHouse(World *world, xRectangle dest)
{
    EntityID id = ENTITY_HOUSE;
    xRectangle source = RECT_HOUSE;
    xRectangle collider =
    {
        dest.x,
        dest.y + 64*6 - 68,
        dest.width,
        128
    };

    xAddObject(world, id, source, dest, collider);
}

void xAddLightPost(World *world, xRectangle dest)
{
    EntityID id = ENTITY_LIGHT_POST;
    xRectangle source = RECT_LIGHT_POST;
    xRectangle collider =
    {
        dest.x,
        dest.y + dest.height - 20,
        dest.width,
        20
    };
    
    xAddObject(world, id, source, dest, collider);
}

void xAddRock(World *world, RockType type, xRectangle dest)
{
    xRectangle source;
    xRectangle collider;

    EntityID id;

    switch (type)
    {
        case ROCK_SMALL:

        id = ENTITY_ROCK_SMALL;
        source = RECT_ROCK_SMALL;

        collider = (xRectangle){
            dest.x + 8,
            dest.y + dest.height - 18,
            dest.width - 10,
            16
        };
        break;

        case ROCK_LARGE:
        
        id = ENTITY_ROCK_LARGE;
        source = RECT_ROCK_LARGE;

        collider = (xRectangle){
            dest.x,
            dest.y + dest.height - 20,
            dest.width,
            20
        };
        break;
    }

    xAddObject(world, id, source, dest, collider);

}

void xAddStone(World *world, StoneType type, xRectangle dest)
{
    xRectangle source;
    xRectangle collider;

    EntityID id;

    switch (type)
    {
        case STONE_SMALL:

        id = STONE_SMALL;
            source = RECT_STONE_SMALL;

            collider = (xRectangle){
                dest.x + 12,
                dest.y + 36,
                38,
                20,
            };
            break;

        case STONE_MEDIUM:

            id = STONE_MEDIUM;
            source = RECT_STONE_MEDIUM;

            collider = (xRectangle){
                dest.x + 14,
                dest.y + 36,
                42,
                20,
            };
        break;

        case STONE_LARGE:

            id = STONE_LARGE;
            source = RECT_STONE_LARGE;

            collider = (xRectangle){
                dest.x + 8,
                dest.y + 36,
                50,
                20,
            };
        break;
    }

    xAddObject(world, id, source, dest, collider);
}

void xAddTree(World *world, TreeStage stage, xRectangle dest)
{
    xRectangle source;
    xRectangle collider;

    EntityID id;

    switch (stage)
    {
        case TREE_STUMP:

        id = ENTITY_TREE_STUMP;
            source = RECT_TREE_STUMP;
            
            collider = (xRectangle){
                dest.x,
                dest.y + dest.height - 16,
                dest.width - 2,
                8
            };
        break;

        case TREE_CUT:

            id = ENTITY_TREE_CUT;
            source = RECT_TREE_CUT;

            collider = (xRectangle){
                dest.x + 4,
                dest.y + 38,
                56,
                20,
            };
        break;

        case TREE_SMALL:

            id = ENTITY_TREE_SMALL;
            source = RECT_TREE_SMALL;

            collider = (xRectangle){
                dest.x + dest.width / 2 - 15,
                dest.y + 90,
                28,
                20,
            };
        break;

        case TREE_LARGE:

            id = ENTITY_TREE_LARGE;
            source = RECT_TREE_LARGE;

            collider = (xRectangle){
                dest.x + dest.width/2 - 26,
                dest.y + 206,
                58,
                20,
            };
        break;
    }

    xAddObject(world, id, source, dest, collider);
}

void xAddMushroom(World *world, xRectangle dest)
{
    xRectangle source;
    xRectangle collider;

    EntityID id = ENTITY_MUSHROOM;
    source = RECT_MUSHROOM;

    collider = (xRectangle)
    {
        dest.x + 4,
        dest.y + 20,
        dest.width - 8,
        8
    };

    xAddObject(world, id, source, dest, collider);
}
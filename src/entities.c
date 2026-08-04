#include "entities.h"
#include "sprites.h"

/* -------------------- Signatures -------------------- */

static void xSetFadeCollision(xGameObject *object, EntityID id);

static bool xAlwaysBelowPlayer(EntityID id);

/* -------------------- ----------- -------------------- */

static void xAddEntity(World *world, EntityID id, xRectangle source, xRectangle dest, xRectangle collider)
{
    if (world->entityCount >= MAX_OBJECTS)
        return;

    xGameObject *object = &world->entities[world->entityCount++].gameObject;

    if (id != ENTITY_EMPTY_OBJECT)
    {
        object->texture = world->spriteSheet;
    }
    else if (id == ENTITY_EMPTY_OBJECT)
    {
        object->texture = (Texture2D){0}; // Empty texture
    }

    object->source = source;
    object->dest = dest;

    object->type = OBJECT_ENTITY;

    // Trigger the special case of not wanting collision/fade effect.
    xSetFadeCollision(object, id);

    object->collider = collider;

    if (xAlwaysBelowPlayer(id))
    {
        object->depth = 0;
    }
    else
    {
        object->depth = collider.y + collider.height;
    }

    object->flip = false;
    object->active = true;
}

static void xSetFadeCollision(xGameObject *object, EntityID id)
{
    switch (id)
    {
    case ENTITY_MUSHROOM:
    case ENTITY_ROCK_SMALL:
    case ENTITY_TREE_STUMP:
        object->fadeable = false;
        object->collidable = false;
        break;

    case ENTITY_POND_6x6:
    case ENTITY_GROUND_BLOCK:
    case ENTITY_HIGH_GROUND_BLOCK:
    case ENTITY_EMPTY_OBJECT:
        object->fadeable = false;
        object->collidable = true;
        break;

    default:
        object->fadeable = true;
        object->collidable = true;
        break;
    }
}

static bool xAlwaysBelowPlayer(EntityID id)
{
    switch (id)
    {
    case ENTITY_EMPTY_OBJECT:
    case ENTITY_POND_6x6:
    case ENTITY_GROUND_BLOCK:
    case ENTITY_HIGH_GROUND_BLOCK:
        return true;
        break;

    default:
        return false;
        break;
    }
}

void xAddHouse(World *world, xRectangle dest)
{
    EntityID id = ENTITY_HOUSE;
    xRectangle source = RECT_HOUSE;
    xRectangle collider =
        {
            dest.x,
            dest.y + 64 * 6 - 68,
            dest.width,
            128};

    xAddEntity(world, id, source, dest, collider);
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
            20};

    xAddEntity(world, id, source, dest, collider);
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
            16};
        break;

    case ROCK_LARGE:

        id = ENTITY_ROCK_LARGE;
        source = RECT_ROCK_LARGE;

        collider = (xRectangle){
            dest.x,
            dest.y + dest.height - 20,
            dest.width,
            20};
        break;
    }

    xAddEntity(world, id, source, dest, collider);
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

    xAddEntity(world, id, source, dest, collider);
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
            8};
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
            dest.x + dest.width / 2 - 26,
            dest.y + 206,
            58,
            20,
        };
        break;
    }

    xAddEntity(world, id, source, dest, collider);
}

void xAddMushroom(World *world, xRectangle dest)
{
    xRectangle source;

    EntityID id = ENTITY_MUSHROOM;
    source = RECT_MUSHROOM;

    xRectangle collider =
        {
            dest.x + 4,
            dest.y + 20,
            dest.width - 8,
            8};

    xAddEntity(world, id, source, dest, collider);
}

void xAddPond6x6(World *world, xRectangle dest)
{
    xRectangle source = RECT_POND;
    EntityID id = ENTITY_POND_6x6;

    xRectangle collider =
        {
            dest.x + 32,
            dest.y + 32,
            64 * 5,
            64 * 4};

    xAddEntity(world, id, source, dest, collider);
}

void xAddGroundBlock(World *world, xRectangle dest)
{
    xRectangle source = RECT_GROUND_BLOCK;
    EntityID id = ENTITY_GROUND_BLOCK;

    xRectangle collider =
        {
            dest.x + 16,
            dest.y + 20,
            dest.width - 32,
            dest.height - 36};

    xAddEntity(world, id, source, dest, collider);
}

void xAddFlower(World *world, FlowerColor color, FlowerStage stage, xRectangle dest)
{
    xRectangle source;
    EntityID id;

    if (color == FLOWER_RED)
    {
        id = ENTITY_FLOWER_RED;

        switch (stage)
        {
        case FLOWER_STAGE_1:
            source = RECT_FLOWER_RED_1;
        break;

        case FLOWER_STAGE_2:
            source = RECT_FLOWER_RED_2;
        break;

        case FLOWER_STAGE_3:
            source = RECT_FLOWER_RED_3;
        break;

        case FLOWER_STAGE_4:
            source = RECT_FLOWER_RED_4;
        break;

        default:
            source = RECT_FLOWER_RED_1;
        break;
        }
    }
    else if (color == FLOWER_YELLOW)
    {
        id = ENTITY_FLOWER_YELLOW;

        switch (stage)
        {
        case FLOWER_STAGE_1:
            source = RECT_FLOWER_YELLOW_1;
        break;

        case FLOWER_STAGE_2:
            source = RECT_FLOWER_YELLOW_2;
        break;

        case FLOWER_STAGE_3:
            source = RECT_FLOWER_YELLOW_3;
        break;

        case FLOWER_STAGE_4:
            source = RECT_FLOWER_YELLOW_4;
        break;

        default:
            source = RECT_FLOWER_YELLOW_1;
        break;
        }
    }

    xRectangle collider =
        {
            dest.x + 4,
            dest.y + 20,
            dest.width - 8,
            8};

    xAddEntity(world, id, source, dest, collider);
}

void xAddEmptyEntity(World *world, xRectangle dest)
{
    xRectangle source = {0, 0, 0, 0};
    EntityID id = ENTITY_EMPTY_OBJECT;

    xRectangle collider = dest;

    xAddEntity(world, id, source, dest, collider);
}
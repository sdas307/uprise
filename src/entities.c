#include "entities.h"
#include "sprites.h"

static void xCreateEntity(World *world, const EntityInfo *info)
{
    if (world->entityCount >= MAX_OBJECTS)
        return;

    xGameObject *object = &world->entities[world->entityCount++].gameObject;

    object->texture = *info->spritesheet;

    object->source = info->source;
    object->dest = info->dest;
    object->collider = info->collider;
    object->fadeArea = info->fadeArea;

    object->type = OBJECT_ENTITY;

    object->fadeable = info->fadeable;
    object->collidable = info->collidable;

    object->depth = info->alwaysBelowPlayer ? 0 : info->collider.y + info->collider.height;

    object->flip = info->flip;
    object->active = info->active;
}

void xAddHouse(World *world, HouseType type, xRectangle dest)
{
    EntityInfo info =
    {
        .id = ENTITY_HOUSE,
        .dest = dest,
        .fadeable = true,
        .collidable = true,
        .flip = false,
        .active = true,
        .alwaysBelowPlayer = false
    };
    
    switch (type)
    {
    case HOUSE_TYPE_WOOD_CABIN:

        info.source = RECT_HOUSE_WOOD_CABIN;
        info.spritesheet = &world->spritesheets[SHEET_STRUCTURE_HOUSE_WOOD];

        info.collider = (xRectangle)
        {
            dest.x + 64,
            dest.y + dest.height - 64*3 + 12,
            dest.width - 128,
            128
        };

        info.fadeArea = (xRectangle)
        {
            dest.x + 64,
            dest.y + 64,
            dest.width - 128,
            dest.height - 128
        };

        break;
    
    default:

        info.source = RECT_HOUSE_WOOD_CABIN;
        info.spritesheet = &world->spritesheets[SHEET_STRUCTURE_HOUSE_WOOD];

        break;
    }

    xCreateEntity(world, &info);
}

void xAddLightPost(World *world, xRectangle dest)
{
    EntityInfo info =
    {
        .id = ENTITY_LIGHT_POST,
        .source = RECT_LIGHT_POST_WOOD_1,
        .spritesheet = &world->spritesheets[SHEET_STRUCTURE_FENCE_POSTS],
        .dest = dest,
        .fadeable = true,
        .collidable = true,
        .active = true,
        .alwaysBelowPlayer = false
    };

    info.collider = (xRectangle)
    {
        dest.x + 16,
        dest.y + dest.height - 28,
        dest.width - 28,
        20
    };

    info.fadeArea = (xRectangle)
    {
        dest.x + 28,
        dest.y + 48,
        dest.width - 52,
        dest.height - 24 - 48
    };

    xCreateEntity(world, &info);
}

// void xAddRock(World *world, RockType type, xRectangle dest)
// {
//     xRectangle source;
//     xRectangle collider;

//     EntityID id;

//     switch (type)
//     {
//     case ROCK_SMALL:

//         id = ENTITY_ROCK_SMALL;
//         source = RECT_ROCK_SMALL;

//         collider = (xRectangle){
//             dest.x + 8,
//             dest.y + dest.height - 18,
//             dest.width - 10,
//             16
//         };
//         break;

//     case ROCK_LARGE:

//         id = ENTITY_ROCK_LARGE;
//         source = RECT_ROCK_LARGE;

//         collider = (xRectangle){
//             dest.x,
//             dest.y + dest.height - 20,
//             dest.width,
//             20};
//         break;
//     }

//     xCreateEntity(world, id, source, dest, collider);
// }

// void xAddStone(World *world, StoneType type, xRectangle dest)
// {
//     xRectangle source;
//     xRectangle collider;

//     EntityID id;

//     switch (type)
//     {
//     case STONE_SMALL:

//         id = STONE_SMALL;
//         source = RECT_STONE_SMALL;

//         collider = (xRectangle){
//             dest.x + 12,
//             dest.y + 36,
//             38,
//             20,
//         };
//         break;

//     case STONE_MEDIUM:

//         id = STONE_MEDIUM;
//         source = RECT_STONE_MEDIUM;

//         collider = (xRectangle){
//             dest.x + 14,
//             dest.y + 36,
//             42,
//             20,
//         };
//         break;

//     case STONE_LARGE:

//         id = STONE_LARGE;
//         source = RECT_STONE_LARGE;

//         collider = (xRectangle){
//             dest.x + 8,
//             dest.y + 36,
//             50,
//             20,
//         };
//         break;
//     }

//     xCreateEntity(world, id, source, dest, collider);
// }

void xAddTree(World *world, TreeType type, TreeStage stage, xRectangle dest)
{
    EntityInfo info =
    {
        .spritesheet = &world->spritesheets[SHEET_NATURE_TREE],
        .dest = dest,
        .fadeable = true,
        .collidable = true,
        .alwaysBelowPlayer = false,
        .flip = false,
        .active = true        
    };

    switch (type)
    {
    case TREE_TYPE_BIRCH:
        /* code */
        break;
    
    case TREE_TYPE_OAK:

        switch (stage)
        {
        case TREE_STAGE_LARGE:
            
            info.id = ENTITY_TREE_OAK_LARGE;

            info.source = RECT_TREE_OAK_LARGE;

            info.collider = (xRectangle)
            {
                dest.x + dest.width / 2 - 32,
                dest.y + 236,
                64,
                20,
            };

            info.fadeArea = (xRectangle)
            {
                dest.x + 44 + 10,
                dest.y + 40,
                dest.width - 44 - 52 - 20,
                dest.height - 40 - 64 - 20 - 36
            };

            break;

        default:

            info.id = ENTITY_TREE_OAK_LARGE;

            info.source = RECT_TREE_OAK_LARGE;

            info.collider = (xRectangle)
            {
                dest.x + dest.width / 2 - 26,
                dest.y + 206,
                58,
                20,
            };
            break;
        }
        break;

    default:

        info.source = RECT_TREE_OAK_LARGE;

        info.collider = (xRectangle)
        {
            dest.x + dest.width / 2 - 26,
            dest.y + 206,
            58,
            20,
        };
        break;
    }

    xCreateEntity(world, &info);
}

void xAddGrassTuft(World *world, xRectangle dest)
{
    EntityInfo info =
    {
        .id = ENTITY_GRASS,
        .spritesheet = &world->spritesheets[SHEET_NATURE_GRASS_WILDFLOWERS],
        .source = RECT_GRASS_TUFT,
        .dest = dest,
        .fadeable = false,
        .collidable = false,
        .alwaysBelowPlayer = true,
        .flip = false,
        .active = true
    };

    info.collider = (xRectangle)
    {
        0
    };

    info.fadeArea = (xRectangle)
    {
        0
    };

    xCreateEntity(world, &info);
}

void xAddMushroom(World *world, MushroomType type, xRectangle dest)
{
    EntityInfo info =
    {
        .id = ENTITY_MUSHROOM,
        .spritesheet = &world->spritesheets[SHEET_NATURE_FLOWER_MUSHROOMS],
        .dest = dest,
        .fadeable = false,
        .collidable = false,
        .alwaysBelowPlayer = false,
        .flip = false,
        .active = true
    };
    
    switch (type)
    {
    case MUSHROOM_TYPE_RED:
        info.source = RECT_MUSHROOM_RED;
        break;
    
    default:
        break;
    }

    info.collider = (xRectangle)
    {
        dest.x + 4,
        dest.y + 20,
        dest.width - 8,
        8
    };

    info.fadeArea = (xRectangle)
    {
        0
    };

    xCreateEntity(world, &info);
}

// void xAddFlower(World *world, FlowerColor color, FlowerType type, xRectangle dest)
// {
//     xRectangle source;
//     EntityID id;

//     if (color == FLOWER_RED)
//     {
//         id = ENTITY_FLOWER;

//         switch (type)
//         {
//         case FLOWER_1:
//             source = RECT_FLOWER_RED_1;
//             break;

//         case FLOWER_2:
//             source = RECT_FLOWER_RED_2;
//             break;

//         case FLOWER_3:
//             source = RECT_FLOWER_RED_3;
//             break;

//         case FLOWER_4:
//             source = RECT_FLOWER_RED_4;
//             break;

//         default:
//             source = RECT_FLOWER_RED_1;
//             break;
//         }
//     }
//     else if (color == FLOWER_YELLOW)
//     {
//         id = ENTITY_FLOWER;

//         switch (type)
//         {
//         case FLOWER_1:
//             source = RECT_FLOWER_YELLOW_1;
//             break;

//         case FLOWER_2:
//             source = RECT_FLOWER_YELLOW_2;
//             break;

//         case FLOWER_3:
//             source = RECT_FLOWER_YELLOW_3;
//             break;

//         case FLOWER_4:
//             source = RECT_FLOWER_YELLOW_4;
//             break;

//         default:
//             source = RECT_FLOWER_YELLOW_1;
//             break;
//         }
//     }

//     xRectangle collider =
//         {
//             dest.x + 16,
//             dest.y + 36,
//             30,
//             16
//         };

//     xCreateEntity(world, id, source, dest, collider);
// }

// void xAddEmptyEntity(World *world, xRectangle dest)
// {
//     xRectangle source = {0, 0, 0, 0};
//     Texture2D *spritesheet = &(Texture2D){0};
//     EntityID id = ENTITY_EMPTY_OBJECT;

//     xRectangle collider = dest;

//     xCreateEntity(world, id, source, dest, collider);
// }
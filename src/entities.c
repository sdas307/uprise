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

        info.source = SRC_HOUSE_WOOD_CABIN;
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

        info.source = SRC_HOUSE_WOOD_CABIN;
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
        .source = SRC_LIGHT_POST_WOOD_1,
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
//         source = SRC_ROCK_SMALL;

//         collider = (xRectangle){
//             dest.x + 8,
//             dest.y + dest.height - 18,
//             dest.width - 10,
//             16
//         };
//         break;

//     case ROCK_LARGE:

//         id = ENTITY_ROCK_LARGE;
//         source = SRC_ROCK_LARGE;

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
//         source = SRC_STONE_SMALL;

//         collider = (xRectangle){
//             dest.x + 12,
//             dest.y + 36,
//             38,
//             20,
//         };
//         break;

//     case STONE_MEDIUM:

//         id = STONE_MEDIUM;
//         source = SRC_STONE_MEDIUM;

//         collider = (xRectangle){
//             dest.x + 14,
//             dest.y + 36,
//             42,
//             20,
//         };
//         break;

//     case STONE_LARGE:

//         id = STONE_LARGE;
//         source = SRC_STONE_LARGE;

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

            info.source = SRC_TREE_OAK_LARGE;

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

            info.source = SRC_TREE_OAK_LARGE;

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

        info.source = SRC_TREE_OAK_LARGE;

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
        .source = SRC_GRASS_TUFT,
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
        info.source = SRC_MUSHROOM_RED;
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

void xAddHighGroundBounds(World *world, xRectangle dest)
{
    EntityInfo info =
    {
        .id = ENTITY_HIGH_GROUND_BLOCK,
        .spritesheet = &(Texture2D) {0},
        .source = (xRectangle) {0},
        .dest = dest,
        .fadeable = false,
        .collidable = true,
        .active = true
    };

    info.collider = (xRectangle)
    {
        dest.x + 20,
        dest.y + 24,
        dest.width - 24,
        dest.height - 42
    };

    xCreateEntity(world, &info);
}

void xAddStairs(World *world, xRectangle dest)
{
    EntityInfo info =
    {
        .id = ENTITY_STAIRS,
        .spritesheet = &world->spritesheets[SHEET_NATURE_GRASSLANDS],
        .source = SRC_STAIRS_GROUND,
        .dest = dest,
        .fadeable = false,
        .collidable = false,
        .active = true,
        .alwaysBelowPlayer = true,
        .flip = false
    };

    info.collider = (xRectangle) {0};

    xCreateEntity(world, &info);
}

void xAddHedge(World *world, HedgePiece piece, xRectangle dest)
{
    EntityInfo info =
    {
        .id = ENTITY_HEDGE,
        .spritesheet = &world->spritesheets[SHEET_NATURE_TREE],
        .dest = dest,
        .fadeable = false,
        .collidable = true,
        .alwaysBelowPlayer = false,
        .active = true,
        .flip = false
    };

    info.collider = (xRectangle)
    {
        dest.x,
        dest.y,
        64,
        64
    };

    switch (piece)
    {
    case HEDGE_VER_TOP:
        info.source = SRC_HEDGE_VER_TOP;
        break;
    
    case HEDGE_VER_CENTER:
        info.source = SRC_HEDGE_VER_CENTER;
        break;

    case HEDGE_VER_BOTTOM:
        info.source = SRC_HEDGE_VER_BOTTOM;
        break;

    case HEDGE_HOR_LEFT:
        info.source = SRC_HEDGE_HOR_LEFT;
        break;
    
    case HEDGE_HOR_CENTER:
        info.source = SRC_HEDGE_HOR_CENTER;
        break;
    
    case HEDGE_HOR_RIGHT:
        info.source = SRC_HEDGE_HOR_RIGHT;
        break;

    case HEDGE_SINGLE:
        info.source = SRC_HEDGE_SINGLE;
        break;
    
    default:
        info.source = SRC_HEDGE_SINGLE;
        break;
    }

    xCreateEntity(world, &info);
}

void xAddWildflowers(World *world, WildflowerVariant variant, xRectangle dest)
{
    EntityInfo info =
    {
        .id = ENTITY_WILDFLOWER,
        .spritesheet = &world->spritesheets[SHEET_NATURE_GRASS_WILDFLOWERS],
        .dest = dest,
        .collider = (xRectangle) {0},
        .fadeable = false,
        .collidable = false,
        .alwaysBelowPlayer = true,
        .flip = false,
        .active = true
    };

    switch (variant)
    {
    case WF_VAR_YELLOW_1:
        info.source = SRC_WF_YELLOW_1;
        break;

    case WF_VAR_YELLOW_2:
        info.source = SRC_WF_YELLOW_2;
        break;

    case WF_VAR_YELLOW_3:
        info.source = SRC_WF_YELLOW_3;
        break;

    case WF_VAR_WHITE_1:
        info.source = SRC_WF_WHITE_1;
        break;

    case WF_VAR_WHITE_2:
        info.source = SRC_WF_WHITE_2;
        break;

    case WF_VAR_WHITE_3:
        info.source = SRC_WF_WHITE_3;
        break;

    case WF_VAR_RED_1:
        info.source = SRC_WF_RED_1;
        break;

    case WF_VAR_RED_2:
        info.source = SRC_WF_RED_2;
        break;

    case WF_VAR_RED_3:
        info.source = SRC_WF_RED_3;
        break;

    case WF_VAR_PINK_1:
        info.source = SRC_WF_PINK_1;
        break;

    case WF_VAR_PINK_2:
        info.source = SRC_WF_PINK_2;
        break;

    case WF_VAR_PINK_3:
        info.source = SRC_WF_PINK_3;
        break;

    case WF_VAR_CYAN_1:
        info.source = SRC_WF_CYAN_1;
        break;

    case WF_VAR_CYAN_2:
        info.source = SRC_WF_CYAN_2;
        break;

    case WF_VAR_CYAN_3:
        info.source = SRC_WF_CYAN_3;
        break;
    
    default:
        info.source = SRC_WF_YELLOW_1;
        break;
    }

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
//             source = SRC_FLOWER_RED_1;
//             break;

//         case FLOWER_2:
//             source = SRC_FLOWER_RED_2;
//             break;

//         case FLOWER_3:
//             source = SRC_FLOWER_RED_3;
//             break;

//         case FLOWER_4:
//             source = SRC_FLOWER_RED_4;
//             break;

//         default:
//             source = SRC_FLOWER_RED_1;
//             break;
//         }
//     }
//     else if (color == FLOWER_YELLOW)
//     {
//         id = ENTITY_FLOWER;

//         switch (type)
//         {
//         case FLOWER_1:
//             source = SRC_FLOWER_YELLOW_1;
//             break;

//         case FLOWER_2:
//             source = SRC_FLOWER_YELLOW_2;
//             break;

//         case FLOWER_3:
//             source = SRC_FLOWER_YELLOW_3;
//             break;

//         case FLOWER_4:
//             source = SRC_FLOWER_YELLOW_4;
//             break;

//         default:
//             source = SRC_FLOWER_YELLOW_1;
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
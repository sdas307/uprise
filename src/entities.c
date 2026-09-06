#include "entities.h"
#include "sprites.h"

static void xCreateEntity(World *world, const EntityInfo *info, const Animation *animation)
{
    if (world->entityCount >= MAX_OBJECTS)
        return;

    xGameObject *object = &world->entities[world->entityCount].gameObject;

    object->texture = *info->spritesheet;

    object->source = info->source;
    object->dest = info->dest;
    object->collider = info->collider;
    object->fadeArea = info->fadeArea;

    object->type = OBJECT_ENTITY;

    object->fadeable = info->fadeable;
    object->collidable = info->collidable;

    object->depth = info->alwaysBelowPlayer ? 0 : info->collider.y + info->collider.height;
    
    world->entities[world->entityCount].interactionID = info->interactionID;

    object->flip = info->flip;
    object->active = info->active;

    if (animation)
        object->animation = *animation;
    else
        object->animation = (Animation) {0};

    // Update entity count for the next entity.
    world->entityCount++;
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
        .alwaysBelowPlayer = false,
        .interactionID = INTERACTION_NONE
    };

    Animation animation = {0};
    
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

    xCreateEntity(world, &info, &animation);
}

void xAddLightPost(World *world, xRectangle dest)
{
    EntityInfo info =
    {
        .id = ENTITY_LIGHT_POST,
        .source = SRC_LIGHT_POST_WOOD_1[0],
        .spritesheet = &world->spritesheets[SHEET_STRUCTURE_FENCE_POSTS],
        .dest = dest,
        .fadeable = true,
        .collidable = true,
        .active = true,
        .alwaysBelowPlayer = false,
        .interactionID = INTERACTION_NONE
    };

    Animation animation =
    {
        .active = true,
        .frameCount = 6,
        .frames = SRC_LIGHT_POST_WOOD_1,
        .currentFrame = 0,
        .frameTime = 0.25f,
        .timer = 0.0f
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

    xCreateEntity(world, &info, &animation);
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
        .active = true,
        .interactionID = INTERACTION_DESTROY,
    };

    Animation animation = {0};

    switch (type)
    {
    case TREE_TYPE_BIRCH:

        switch (stage)
        {
        case TREE_STAGE_LARGE:
            
            info.id = ENTITY_TREE_BIRCH_LARGE;

            info.source = SRC_TREE_BIRCH_LARGE;

            info.collider = (xRectangle)
            {
                dest.x + dest.width / 2 - 24,
                dest.y + 236,
                48,
                20,
            };

            info.fadeArea = (xRectangle)
            {
                dest.x + 52,
                dest.y + 48,
                dest.width - 44 - 60,
                dest.height - 40 - 64 - 20 - 44
            };
            break;
        
        default:
            break;
        }
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

    xCreateEntity(world, &info, &animation);
}

void xAddMushroom(World *world, MushroomType type, xRectangle dest)
{
    EntityInfo info =
    {
        .id = ENTITY_MUSHROOM,
        .spritesheet = &world->spritesheets[SHEET_NATURE_FLOWER_MUSHROOMS],
        .dest = dest,
        .fadeable = false,
        .fadeArea = {0},
        .collidable = false,
        .collider = {0},
        .alwaysBelowPlayer = false,
        .flip = false,
        .active = true,
        .interactionID = INTERACTION_NONE
    };

    Animation animation = {0};
    
    switch (type)
    {
    case MUSHROOM_TYPE_RED:
        info.source = SRC_MUSHROOM_RED;
        break;
    
    default:
        break;
    }

    xCreateEntity(world, &info, &animation);
}

void xAddUpperLayerColliders(World *world, int index, xRectangle dest)
{
    EntityInfo info =
    {
        .id = ENTITY_HIGH_GROUND_BLOCK,
        .spritesheet = &(Texture2D) {0},
        .source = (xRectangle) {0},
        .dest = dest,
        .fadeable = false,
        .collidable = true,
        .active = true,
        .interactionID = INTERACTION_NONE
    };

    Animation animation = {0};

    switch (index)
    {
    case 1:
        info.collider = (xRectangle)
        {
            dest.x + 32,
            dest.y + 32,
            dest.width - 32,
            dest.height - 32
        };
        break;

    case 2:
        info.collider = (xRectangle)
        {
            dest.x,
            dest.y + 24,
            dest.width,
            dest.height - 24
        };
        break;

     case 4:
        info.collider = (xRectangle)
        {
            dest.x + 20,
            dest.y,
            dest.width - 20 - 12,
            dest.height
        };
        break;

    case 12:
        info.collider = (xRectangle)
        {
            dest.x + 20,
            dest.y,
            dest.width - 24 - 8,
            dest.height - 12
        };
        break;
    
    default:
        break;
    }

    xCreateEntity(world, &info, &animation);
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
        .flip = false,
        .interactionID = INTERACTION_NONE
    };
    
    Animation animation = {0};

    info.collider = (xRectangle) {0};

    xCreateEntity(world, &info, &animation);
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
        .flip = false,
        .interactionID = INTERACTION_NONE
    };

    Animation animation = {0};

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

    xCreateEntity(world, &info, &animation);
}

void xAddCliffStairsCollider(World *world, xRectangle dest)
{
    EntityInfo info =
    {
        .source = {0},
        .spritesheet = &(Texture2D){0},
        .id = ENTITY_EMPTY_OBJECT,
        .active = true,
        .collidable = false,
        .fadeable = false,
        .fadeArea = {0},
        .dest = dest,
        .alwaysBelowPlayer = true,
        .collider = dest,
        .interactionID = INTERACTION_NONE
    };

    Animation animation = {0};

    xCreateEntity(world, &info, &animation);
}

void xAddCliffCollider(World *world, int index, xRectangle dest)
{
    EntityInfo info =
    {
        .source = {0},
        .spritesheet = &(Texture2D){0},
        .id = ENTITY_EMPTY_OBJECT,
        .active = true,
        .collidable = true,
        .fadeable = false,
        .fadeArea = {0},
        .dest = dest,
        .interactionID = INTERACTION_NONE
    };

    Animation animation = {0};

    switch (index)
    {
    case 5:

        info.collider = (xRectangle)
        {
            .x = dest.x + 24,
            .y = dest.y,
            .width = dest.width - 8 - 24,
            .height = dest.height
        };

        break;

    case 7:

        info.collider = (xRectangle)
        {
            .x = dest.x,
            .y = dest.y + 24,
            .width = dest.width,
            .height = dest.height - 24
        };

        break;

    case 8:

        info.collider = (xRectangle)
        {
            .x = dest.x + 24,
            .y = dest.y,
            .width = dest.width - 24 - 8,
            .height = dest.height
        };

        break;

    case 10:

        info.collider = (xRectangle)
        {
            .x = dest.x,
            .y = dest.y,
            .width = dest.width,
            .height = dest.height
        };

        break;

    case 11:

        info.collider = (xRectangle)
        {
            .x = dest.x,
            .y = dest.y,
            .width = dest.width - 8,
            .height = dest.height
        };

        break;

    case 13:

        info.collider = (xRectangle)
        {
            .x = dest.x,
            .y = dest.y,
            .width = dest.width,
            .height = dest.height
        };

        break;

    case 14:

        info.collider = (xRectangle)
        {
            .x = dest.x,
            .y = dest.y,
            .width = dest.width - 8,
            .height = dest.height
        };

        break;
    
    default:
        break;
    }

    xCreateEntity(world, &info, &animation);
}

void xAddFarmland(World *world, int index, xRectangle dest)
{
    EntityInfo info =
    {
        .id = ENTITY_FARMLAND_DRY,
        .active = true,
        .spritesheet = &world->spritesheets[SHEET_NATURE_GRASSLANDS],
        .collidable = false,
        .collider = dest,
        .alwaysBelowPlayer = true,
        .fadeable = false,
        .fadeArea = {0},
        .dest = dest,
        .interactionID = INTERACTION_FARMLAND_WATER
    };

    Animation animation = {0};

    switch (index)
    {
    case 1:
        info.source = SRC_FARMLAND_DRY[TOP_LEFT];
        break;

    case 2:
        info.source = SRC_FARMLAND_DRY[TOP_CENTER];
        break;

    case 3:
        info.source = SRC_FARMLAND_DRY[TOP_RIGHT];
        break;

    case 4:
        info.source = SRC_FARMLAND_DRY[CENTER_LEFT];
        break;

    case 5:
        info.source = SRC_FARMLAND_DRY[CENTER_CENTER];
        break;

    case 6:
        info.source = SRC_FARMLAND_DRY[CENTER_RIGHT];
        break;

    case 7:
        info.source = SRC_FARMLAND_DRY[BOTTOM_LEFT];
        break;

    case 8:
        info.source = SRC_FARMLAND_DRY[BOTTOM_CENTER];
        break;

    case 9:
        info.source = SRC_FARMLAND_DRY[BOTTOM_RIGHT];
        break;
    
    default:
        info.source = (xRectangle){0};
        break;
    }
    
    xCreateEntity(world, &info, &animation);
}
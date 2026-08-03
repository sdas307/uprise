#ifndef SPRITES_H
#define SPRITES_H

#include "xEngine.h"

// ########## TRY THIS FOR ANIMATED OBJECTS ##########

// typedef enum SpriteID
// {
//     /* ---------- World Objects ---------- */

//     SPRITE_TREE_SMALL, SPRITE_TREE_LARGE,
//     SPRITE_TREE_STUMP, SPRITE_TREE_CUT,

//     SPRITE_ROCK_SMALL, SPRITE_ROCK_LARGE,

//     SPRITE_STONE_SMALL, SPRITE_STONE_MEDIUM,
//     SPRITE_STONE_LARGE,

//     SPRITE_MUSHROOM,

//     /* ---------- Buildings ---------- */

//     SPRITE_HOUSE,
//     SPRITE_LIGHT_POST,

//     /* ---------- Animals ---------- */

//     SPRITE_ANIMAL_CHICKEN,
//     SPRITE_ANIMAL_COW,
//     SPRITE_ANIMAL_PIG,
//     SPRITE_ANIMAL_SHEEP
    
// } SpriteID;

/// Get sprite source rectangle.
// const xRectangle *xGetSprite(SpriteID id);

#pragma region Animal Sprites

extern const xRectangle RECT_CHICKEN;

extern const xRectangle RECT_SHEEP;

extern const xRectangle RECT_PIG;

extern const xRectangle RECT_COW;

#pragma endregion

#pragma region Buildings

extern const xRectangle RECT_HOUSE;
extern const xRectangle RECT_LIGHT_POST;

#pragma endregion

#pragma region World Objects

extern const xRectangle RECT_TREE_CUT;
extern const xRectangle RECT_TREE_STUMP;
extern const xRectangle RECT_TREE_SMALL;
extern const xRectangle RECT_TREE_LARGE;

extern const xRectangle RECT_ROCK_SMALL;
extern const xRectangle RECT_ROCK_LARGE;

extern const xRectangle RECT_STONE_SMALL;
extern const xRectangle RECT_STONE_MEDIUM;
extern const xRectangle RECT_STONE_LARGE;

extern const xRectangle RECT_MUSHROOM;

extern const xRectangle RECT_FLOWER_RED_1;
extern const xRectangle RECT_FLOWER_RED_2;
extern const xRectangle RECT_FLOWER_RED_3;
extern const xRectangle RECT_FLOWER_RED_4;

extern const xRectangle RECT_FLOWER_YELLOW_1;
extern const xRectangle RECT_FLOWER_YELLOW_2;
extern const xRectangle RECT_FLOWER_YELLOW_3;
extern const xRectangle RECT_FLOWER_YELLOW_4;

extern const xRectangle RECT_POND;

extern const xRectangle RECT_GROUND_BLOCK;
extern const xRectangle RECT_HIGH_GROUND_TOP_LEFT;
extern const xRectangle RECT_HIGH_GROUND_TOP_CENTER;
extern const xRectangle RECT_HIGH_GROUND_TOP_RIGHT;
extern const xRectangle RECT_HIGH_GROUND_CENTER_LEFT;
extern const xRectangle RECT_HIGH_GROUND_CENTER_CENTER;
extern const xRectangle RECT_HIGH_GROUND_CENTER_RIGHT;
extern const xRectangle RECT_HIGH_GROUND_BOTTOM_LEFT;
extern const xRectangle RECT_HIGH_GROUND_BOTTOM_CENTER;
extern const xRectangle RECT_HIGH_GROUND_BOTTOM_RIGHT;

#pragma endregion

#endif
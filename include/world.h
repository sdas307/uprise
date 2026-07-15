#ifndef MAP_OBJECTS_H
#define MAP_OBJECTS_H

#include "raylib.h"
#include "xEngine.h"
#include "animal.h"

#define MAX_OBJECTS 128

typedef struct Terrain
{
    Texture2D texture;
    xRectangle source;
    xRectangle dest;

} Terrain;

typedef struct World
{
    Terrain terrain;    /// Terrain Image and position rectangles.

    Texture2D spriteSheet;  /// Objects sprite sheet.

    xGameObject objects[MAX_OBJECTS];
    int objectCount;

} World;

#pragma region Types of World Objects
typedef enum StoneType
{
    STONE_SMALL,
    STONE_MEDIUM,
    STONE_LARGE
    
} StoneType;

typedef enum TreeStage
{
    TREE_STUMP,
    TREE_CUT,
    TREE_SMALL,
    TREE_LARGE
    
} TreeStage;

typedef enum RockType
{
    ROCK_SMALL,
    ROCK_LARGE,
    
} RockType;

typedef enum CarrotStage
{
    CARROT_STAGE_1,
    CARROT_STAGE_2,
    CARROT_STAGE_3,
    CARROT_STAGE_4
    
} CarrotStage;

typedef enum RedFlowerStage
{
    RED_FLOWER_STAGE_1,
    RED_FLOWER_STAGE_2,
    RED_FLOWER_STAGE_3,
    RED_FLOWER_STAGE_4,

} RedFlowerStage;

typedef enum YellowFlowerStage
{
    YELLOW_FLOWER_STAGE_1,
    YELLOW_FLOWER_STAGE_2,
    YELLOW_FLOWER_STAGE_3,
    YELLOW_FLOWER_STAGE_4,

} YellowFlowerStage;

typedef enum RedFlowerPotStage
{
    RED_FLOWER_POT_STAGE_1,
    RED_FLOWER_POT_STAGE_2,
    RED_FLOWER_POT_STAGE_3,
    RED_FLOWER_POT_STAGE_4,

} RedFlowerPotStage;

typedef enum YellowFlowerPotStage
{
    YELLOW_FLOWER_POT_STAGE_1,
    YELLOW_FLOWER_POT_STAGE_2,
    YELLOW_FLOWER_POT_STAGE_3,
    YELLOW_FLOWER_POT_STAGE_4,

} YellowFlowerPotStage;
#pragma endregion

/// Initialize world.
void xInitWorld(World *world);

/// Place all objects in world space.
void xLoadWorld(World *world, AnimalManager *manager);

/// Free world textures from GPU.
void xUnloadWorld(World *world);

#endif
#ifndef MAP_OBJECTS_H
#define MAP_OBJECTS_H

#include "raylib.h"
#include "xEngine.h"
#include "map.h"

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
    ROCK_BIG,
    
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

/// Place all objects on map.
void xLoadMap(Map *map);

#endif
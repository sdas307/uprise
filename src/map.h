#ifndef MAP_H
#define MAP_H    

#include "raylib.h"
#include "xEngine.h"

#define MAX_OBJECTS 128

typedef struct Terrain
{
    Texture2D texture;
    Rectangle source;
    Rectangle dest;

} Terrain;

typedef struct Map
{
    Terrain terrain;    /// Terrain Image and position rectangles.

    Texture2D spriteSheet;  /// Objects sprite sheet.

    xGameObject objects[MAX_OBJECTS];
    int objectCount;

} Map;

/// Initialize Map with a texture and source and destination rectangles.
void xInitMap(Map *map);

void xAddObject(Map *map, Rectangle source, Rectangle dest);

/// Place all objects on map.
void xLoadMap(Map *map);

/// Draw map at its current position.
void xDrawMap(Map *map);

/// Unload map object's texture from vram.
void xUnloadMap(Map *map);

/* ---------- Map Objects ---------- */

typedef enum RockType
{
    ROCK_SMALL,
    ROCK_BIG,
    
} RockType;

typedef enum StoneType
{
    STONE_SMALL,
    STONE_MEDIUM,
    STONE_LARGE
    
} StoneType;

typedef enum CarrotStage
{
    CARROT_STAGE_1,
    CARROT_STAGE_2,
    CARROT_STAGE_3,
    CARROT_STAGE_4
} CarrotStage;

typedef enum TreeStage
{
    TREE_STUMP,
    TREE_CUT,
    TREE_SMALL,
    TREE_LARGE
    
} TreeStage;

typedef enum RedFlowerStage
{
    RF_STAGE_1,
    RF_STAGE_2,
    RF_STAGE_3,
    RF_STAGE_4,

} RedFlowerStage;

typedef enum YellowFlowerStage
{
    YF_STAGE_1,
    YF_STAGE_2,
    YF_STAGE_3,
    YF_STAGE_4,

} YellowFlowerStage;

typedef enum RedFlowerPotStage
{
    RF_POT_STAGE_1,
    RF_POT_STAGE_2,
    RF_POT_STAGE_3,
    RF_POT_STAGE_4,

} RedFlowerPotStage;

typedef enum YellowFlowerPotStage
{
    YF_POT_STAGE_1,
    YF_POT_STAGE_2,
    YF_POT_STAGE_3,
    YF_POT_STAGE_4,

} YellowFlowerPotStage; 

void xAddStone(Map *map, StoneType type, Rectangle dest);

void xAddTree(Map *map, TreeStage stage, Rectangle dest);

#endif
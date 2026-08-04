#ifndef MAP_OBJECTS_H
#define MAP_OBJECTS_H

#include "xEngine.h"

#define MAX_OBJECTS 128

typedef struct Terrain
{
    Texture2D texture;
    xRectangle source;
    xRectangle dest;

} Terrain;

typedef enum EntityID
{
    ENTITY_HOUSE,
    ENTITY_LIGHT_POST,

    ENTITY_TREE_SMALL,
    ENTITY_TREE_LARGE,
    ENTITY_TREE_CUT,
    ENTITY_TREE_STUMP,
    ENTITY_TREE_LOG,

    ENTITY_MUSHROOM,
    ENTITY_FLOWER,
    ENTITY_POTTED_FLOWER,

    ENTITY_ROCK_SMALL,
    ENTITY_ROCK_LARGE,

    ENTITY_STONE_SMALL,
    ENTITY_STONE_MEDIUM,
    ENTITY_STONE_LARGE,

    ENTITY_CROP_WHEAT,
    ENTITY_CROP_CARROT,

    ENTITY_SIGN_WHEAT,
    ENTITY_SIGN_CARROT,

    ENTITY_POND_6x6,

    ENTITY_GROUND_BLOCK,
    ENTITY_HIGH_GROUND_BLOCK,

    ENTITY_EMPTY_OBJECT

} EntityID;

extern EntityID entityID;

typedef struct Entity
{
    xGameObject gameObject;
    EntityID id;
    
    int hp;
    bool harvestable;
    bool destructible;

} Entity;

typedef struct World
{
    Terrain terrain;        /// Terrain Image and position rectangles.

    Texture2D spriteSheet;  /// Objects sprite sheet.

    Entity entities[MAX_OBJECTS];
    int entityCount;

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
    TREE_LARGE,
    TREE_LOG
    
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

typedef enum FlowerColor
{
    FLOWER_RED,
    FLOWER_YELLOW

} FlowerColor;

typedef enum FlowerType
{
    FLOWER_1,
    FLOWER_2,
    FLOWER_3,
    FLOWER_4

} FlowerType;

#pragma endregion

struct AnimalManager;
typedef struct AnimalManager AnimalManager;

/// Initialize world.
void xInitWorld(World *world);

/// Place all objects in world space.
void xLoadWorld(World *world, AnimalManager *manager);

/// Free world textures from GPU.
void xUnloadWorld(World *world);

#endif
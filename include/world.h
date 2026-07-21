#ifndef MAP_OBJECTS_H
#define MAP_OBJECTS_H

#include "xEngine.h"
#include "animal.h"

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
    ENTITY_FLOWER_RED,
    ENTITY_FLOWER_YELLOW,

    ENTITY_POTTED_FLOWER_RED,
    ENTITY_POTTED_FLOWER_YELLOW,

    ENTITY_ROCK_SMALL,
    ENTITY_ROCK_LARGE,

    ENTITY_STONE_SMALL,
    ENTITY_STONE_MEDIUM,
    ENTITY_STONE_LARGE,

    ENTITY_CROP_WHEAT,
    ENTITY_CROP_CARROT,

    ENTITY_SIGN_WHEAT,
    ENTITY_SIGN_CARROT

} EntityID;

extern EntityID entityID;

typedef struct Entity
{
    xGameObject gameObject;
    EntityID id;
    
    int hp;
    bool collidable;
    bool harvestable;
    bool destructible;
    bool fadeable;

} Entity;

typedef struct World
{
    Terrain terrain;    /// Terrain Image and position rectangles.

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

typedef enum FlowerRedStage
{
    RED_FLOWER_STAGE_1,
    RED_FLOWER_STAGE_2,
    RED_FLOWER_STAGE_3,
    RED_FLOWER_STAGE_4,

} RedFlowerStage;

typedef enum FlowerYellowStage
{
    YELLOW_FLOWER_STAGE_1,
    YELLOW_FLOWER_STAGE_2,
    YELLOW_FLOWER_STAGE_3,
    YELLOW_FLOWER_STAGE_4,

} FlowerYellowStage;

typedef enum PottedFlowerRedStage
{
    RED_FLOWER_POT_STAGE_1,
    RED_FLOWER_POT_STAGE_2,
    RED_FLOWER_POT_STAGE_3,
    RED_FLOWER_POT_STAGE_4,

} PottedFlowerRedStage;

typedef enum PottedFlowerYellowStage
{
    YELLOW_FLOWER_POT_STAGE_1,
    YELLOW_FLOWER_POT_STAGE_2,
    YELLOW_FLOWER_POT_STAGE_3,
    YELLOW_FLOWER_POT_STAGE_4,

}  PottedFlowerYellowStage;
#pragma endregion

/// Initialize world.
void xInitWorld(World *world);

/// Place all objects in world space.
void xLoadWorld(World *world, AnimalManager *manager);

/// Free world textures from GPU.
void xUnloadWorld(World *world);

#endif
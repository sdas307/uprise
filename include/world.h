#ifndef MAP_OBJECTS_H
#define MAP_OBJECTS_H

#include "xEngine.h"

#define MAX_OBJECTS 256

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
    ENTITY_STAIRS,

    ENTITY_HEDGE,
    ENTITY_WILDFLOWER,

    ENTITY_TREE_BIRCH_CUT,
    ENTITY_TREE_BIRCH_SMALL,
    ENTITY_TREE_BIRCH_MEDIUM,
    ENTITY_TREE_BIRCH_LARGE,
    
    ENTITY_TREE_OAK_CUT,
    ENTITY_TREE_OAK_SMALL,
    ENTITY_TREE_OAK_MEDIUM,
    ENTITY_TREE_OAK_LARGE,

    ENTITY_TREE_SPRUCE_CUT,
    ENTITY_TREE_SPRUCE_SMALL,
    ENTITY_TREE_SPRUCE_MEDIUM,
    ENTITY_TREE_SPRUCE_LARGE,

    ENTITY_DECOR_LOG,

    ENTITY_GRASS,
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

typedef struct EntityInfo
{
    EntityID id;

    Texture2D *spritesheet;

    xRectangle source;
    xRectangle dest;
    xRectangle collider;
    xRectangle fadeArea;

    bool fadeable;
    bool collidable;
    bool alwaysBelowPlayer;
    bool active;
    bool flip;

} EntityInfo;

typedef struct Entity
{
    xGameObject gameObject;
    EntityID id;
    
    int hp;
    bool harvestable;
    bool destructible;

} Entity;

typedef enum SpriteSheets
{
    SHEET_STRUCTURE_HOUSE_WOOD,
    SHEET_STRUCTURE_FENCE_POSTS,
    SHEET_STRUCTURE_BRIDGE_WALLS,

    SHEET_NATURE_TREE,
    SHEET_NATURE_GRASSLANDS,
    SHEET_NATURE_GRASS_WILDFLOWERS,
    SHEET_NATURE_CROPS_FRUITS,
    SHEET_NATURE_FLOWER_MUSHROOMS,
    SHEET_NATURE_CLIFF,
    SHEET_NATURE_WATER,
    SHEET_NATURE_WATERFALL,
    
    SHEET_CAVE_CAVE,

    SHEET_WEATHER_WEATHER_EFFECTS,

    SHEET_COUNT

} SpriteSheets;

#define MAX_SHEETS 16

typedef struct World
{
    Terrain terrain;        /// Terrain image and position rectangles.

    // Spritesheets
    Texture2D spritesheets[MAX_SHEETS];

    Entity entities[MAX_OBJECTS];
    int entityCount;

} World;

#pragma region Types of World Objects

typedef enum HouseType
{
    HOUSE_TYPE_WOOD_1,
    HOUSE_TYPE_WOOD_2,
    HOUSE_TYPE_WOOD_3,
    HOUSE_TYPE_WOOD_CABIN,

} HouseType;

typedef enum MushroomType
{
    MUSHROOM_TYPE_RED,
    MUSHROOM_TYPE_BLUE,
    MUSHROOM_TYPE_NAKED

} MushroomType;

typedef enum HedgePiece
{
    HEDGE_VER_TOP,
    HEDGE_VER_CENTER,
    HEDGE_VER_BOTTOM,

    HEDGE_HOR_LEFT,
    HEDGE_HOR_CENTER,
    HEDGE_HOR_RIGHT,

    HEDGE_SINGLE

} HedgePiece;

typedef enum GrassVariant
{
    GRASS_VAR_1,
    GRASS_VAR_2,
    GRASS_VAR_3

} GrassVariant;

typedef enum WildflowerVariant
{
    WF_VAR_WHITE_1,
    WF_VAR_WHITE_2,
    WF_VAR_WHITE_3,

    WF_VAR_YELLOW_1,
    WF_VAR_YELLOW_2,
    WF_VAR_YELLOW_3,

    WF_VAR_RED_1,
    WF_VAR_RED_2,
    WF_VAR_RED_3,

    WF_VAR_PINK_1,
    WF_VAR_PINK_2,
    WF_VAR_PINK_3,

    WF_VAR_CYAN_1,
    WF_VAR_CYAN_2,
    WF_VAR_CYAN_3,

} WildflowerVariant;

typedef enum StoneType
{
    STONE_SMALL,
    STONE_MEDIUM,
    STONE_LARGE
    
} StoneType;

typedef enum TreeType
{
    TREE_TYPE_BIRCH,
    TREE_TYPE_OAK,
    TREE_TYPE_SPRUCE

} TreeType;

typedef enum TreeStage
{
    TREE_STAGE_CUT,
    TREE_STAGE_SMALL,
    TREE_STAGE_MEDIUM,
    TREE_STAGE_LARGE
    
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
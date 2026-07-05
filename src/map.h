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

typedef enum StoneType
{
    STONE_SMALL,
    STONE_MEDIUM,
    STONE_LARGE
    
} StoneType;

typedef enum TreeType
{
    TREE_STUMP,
    TREE_CUT,
    TREE_SMALL,
    TREE_LARGE
    
} TreeType;

void xAddStone(Map *map, StoneType type, Rectangle dest);

void xAddTree(Map *map, TreeType type, Rectangle dest);

#endif
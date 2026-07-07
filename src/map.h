#ifndef MAP_H
#define MAP_H    

#include "raylib.h"
#include "xEngine.h"

#define MAX_OBJECTS 128

typedef struct Terrain
{
    Texture2D texture;
    xRectangle source;
    xRectangle dest;

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

/// Draw map at its current position.
void xDrawMap(Map *map);

/// Unload map object's texture from vram.
void xUnloadMap(Map *map);

#endif
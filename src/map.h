#ifndef MAP_H
#define MAP_H    

#include "raylib.h"

typedef struct Map
{
    Texture2D texture;  /// Map image (texture).

    Rectangle source;   /// Map's rectangle.
    Rectangle dest;     /// Screen rectangle.

} Map;

/// Initialize Map with a texture and source and destination rectangles.
void xInitMap(Map *map);

/// Draw map at its current position.
void xDrawMap(Map *map);

/// Unload map object's texture from vram.
void xUnloadMap(Map *map);

#endif
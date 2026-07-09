#ifndef X_ENGINE_H
#define X_ENGINE_H

#include "raylib.h"
#include <stdbool.h>

typedef struct xSprite
{
    Texture2D texture;
    Rectangle source;
    Rectangle dest;

} xSprite;

typedef struct xTransform
{
    Vector2 tranform;       // Transformation vector.

    float rotation;         // Rotation vector (float: 0 to 1).

} xTransform;

typedef struct xGameObject
{
    // xSprite sprite;          // Sprite to draw.
    // xTransform tranform;     // Transformations to be made.

    Texture2D texture;
    
    Rectangle source;
    Rectangle dest;
    Rectangle collider;

    int depth;              // Depth of the object (y + height).

    bool flip;              // Whether to flip the sprite horizontally.
    bool active;            // Whether to draw on screen.

} xGameObject;

typedef Rectangle xRectangle;           /// Alias: raylib's Rectangle
typedef Vector2 xVector2;               /// Alias: raylib's Vector2
typedef Color xColor;                   /// Alias: raylib's Color

/// @brief Check collision between two axis-aligned bounding boxes (AABB).
/// @param a First rectangle
/// @param b Second rectangle
/// @return True if the rectangles overlap; otherwise false.
bool xCheckCollisionAABB(xRectangle a, xRectangle b);

#endif
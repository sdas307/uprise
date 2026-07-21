#ifndef X_ENGINE_H
#define X_ENGINE_H

#include "raylib.h"
#include <stdbool.h>

/// Number of items in an array.
#define ARRAY_COUNT(x) (sizeof(x) / sizeof((x)[0]))

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

/* Special cases are adressed here. */
typedef enum xObjectType
{
    OBJECT_PLAYER,
    OBJECT_ANIMAL,
    OBJECT_MUSHROOM,
    OBJECT_ENTITY

} xObjectType;

typedef struct xGameObject
{
    // xSprite sprite;          // Sprite to draw.
    // xTransform tranform;     // Transformations to be made.

    Texture2D texture;
    
    Rectangle source;
    Rectangle dest;
    Rectangle collider;

    xObjectType type;

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
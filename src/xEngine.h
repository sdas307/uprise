#ifndef X_ENGINE_H
#define X_ENGINE_H

#include "raylib.h"

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

    bool active;            // Whether to draw on screen.

} xGameObject;

#endif
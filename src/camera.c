#include "camera.h"
#include "config.h"
#include "raymath.h"

/* -------------------- Signatures -------------------- */

/// Clamp camera to follow object and stay within defined world bounds.
static void xClampCamera(xGameCamera *gameCamera, const xVector2 objectCenter, float dt);

/// Linearly interpolate camera target values to smoothly chase player position.
/// @param camera Camera position value - x or y.
/// @param player Player position value - x or y.
/// @param smoothing Smoothing value - the lower the slower.
/// @param dt Delta time.
static inline float xCameraLerp(float camera, float player, float smoothing, float dt);

/* -------------------- Implementation -------------------- */

void xInitCamera(xGameCamera *gameCamera, const xGameObject *object)
{
    // Object to target/follow.
    gameCamera->camera.target = (xVector2)
    {
        object->dest.x + object->dest.width / 2.0f,
        object->dest.y + object->dest.height / 2.0f
    };

    // Where to show object on screen.
    gameCamera->camera.offset = (Vector2)
    {
        SCREEN_WIDTH / 2.0f,
        SCREEN_HEIGHT / 2.0f
    };

    gameCamera->camera.rotation = 0.0f;
    gameCamera->camera.zoom = 1.0f;

    gameCamera->bounds = (CameraBoundary)
    {
        .left = SCREEN_WIDTH / 2,
        .right = SCREEN_WIDTH * 2 + SCREEN_WIDTH / 2,
        .up = SCREEN_HEIGHT / 2,
        .down = SCREEN_HEIGHT + SCREEN_HEIGHT / 2
    };

    gameCamera->smoothing = 6.0f;
}

void xUpdateCamera(xGameCamera *gameCamera, const xGameObject *object, float dt)
{
    // Center of the player to keep track of.
    xVector2 objectCenter =
    {
        object->dest.x + object->dest.width / 2.0f,
        object->dest.y + object->dest.height / 2.0f
    };

    // Ensure camera stays on object and within camera bounds.
    xClampCamera(gameCamera, objectCenter, dt);
}

static void xClampCamera(xGameCamera *gameCamera, const xVector2 objectCenter, float dt)
{
    if (objectCenter.x <= gameCamera->bounds.left)
    {
        gameCamera->camera.target.x = xCameraLerp(gameCamera->camera.target.x, gameCamera->bounds.left, gameCamera->smoothing, dt);
    }
    else if (objectCenter.x >= gameCamera->bounds.right)
    {
        gameCamera->camera.target.x = xCameraLerp(gameCamera->camera.target.x, gameCamera->bounds.right, gameCamera->smoothing, dt);
    }
    else
    {
        gameCamera->camera.target.x = xCameraLerp(gameCamera->camera.target.x, objectCenter.x, gameCamera->smoothing,  dt);
    }
    
    if (objectCenter.y <= gameCamera->bounds.up)
    {
        gameCamera->camera.target.y = xCameraLerp(gameCamera->camera.target.y, gameCamera->bounds.up, gameCamera->smoothing,  dt);
    }
    else if (objectCenter.y >= gameCamera->bounds.down)
    {
        gameCamera->camera.target.y = xCameraLerp(gameCamera->camera.target.y, gameCamera->bounds.down, gameCamera->smoothing,  dt);
    }
    else
    {
        gameCamera->camera.target.y = xCameraLerp(gameCamera->camera.target.y, objectCenter.y, gameCamera->smoothing,  dt);
    }
}

void xCameraDebugLines(xCamera2D *camera)
{
    DrawLine((int)camera->target.x, -SCREEN_HEIGHT*10, (int)camera->target.x, SCREEN_HEIGHT*10, YELLOW);
    DrawLine(-SCREEN_WIDTH*10, (int)camera->target.y, SCREEN_WIDTH*10, (int)camera->target.y, YELLOW);
}

static inline float xCameraLerp(float camera, float player, float smoothing, float dt)
{
    // Frame-rate independent smoothing amount calculation.
    float amount = 1.0f - expf(-smoothing * dt);

    return Lerp(camera, player, amount);
}
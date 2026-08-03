#include "camera.h"
#include "config.h"

/* -------------------- Signatures -------------------- */

static void xClampCamera(xGameCamera *gameCamera, const xGameObject *object, xVector2 objectCenter);


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
}

void xUpdateCamera(xGameCamera *gameCamera, const xGameObject *object)
{
    // Center of the player to keep track of.
    xVector2 objectCenter =
    {
        object->dest.x + object->dest.width / 2.0f,
        object->dest.y + object->dest.height / 2.0f
    };

    // Ensure camera stays on object and within camera bounds.
    xClampCamera(gameCamera, object, objectCenter);
}

static void xClampCamera(xGameCamera *gameCamera, const xGameObject *object, xVector2 objectCenter)
{
    if (objectCenter.x <= gameCamera->bounds.left)
    {
        gameCamera->camera.target.x = gameCamera->bounds.left;
    }
    else if (objectCenter.x >= gameCamera->bounds.right)
    {
        gameCamera->camera.target.x = gameCamera->bounds.right;
    }
    else
    {
        gameCamera->camera.target.x = object->dest.x + object->dest.width / 2.0f;
    }
    
    
    if (objectCenter.y <= gameCamera->bounds.up)
    {
        gameCamera->camera.target.y = gameCamera->bounds.up;
    }
    else if (objectCenter.y >= gameCamera->bounds.down)
    {
        gameCamera->camera.target.y = gameCamera->bounds.down;
    }
    else
    {
        gameCamera->camera.target.y = object->dest.y + object->dest.height / 2.0f;
    }
}

void xCameraDebugLines(xCamera2D *camera)
{
    DrawLine((int)camera->target.x, -SCREEN_HEIGHT*10, (int)camera->target.x, SCREEN_HEIGHT*10, YELLOW);
    DrawLine(-SCREEN_WIDTH*10, (int)camera->target.y, SCREEN_WIDTH*10, (int)camera->target.y, YELLOW);
}
#include "camera.h"

void xInitCamera(xCamera2D *camera, const xGameObject *player)
{
    // Object to target/follow.
    camera->target = (xVector2)
    {
        player->dest.x + player->dest.width / 2.0f,
        player->dest.y + player->dest.height / 2.0f
    };

    // Where to show object on screen.
    camera->offset = (Vector2)
    {
        GetScreenWidth() / 2.0f,
        GetScreenHeight() / 2.0f
    };

    camera->rotation = 0.0f;
    camera->zoom = 1.0f;
}

void xUpdateCamera(xCamera2D *camera, const xGameObject *player)
{
    xVector2 playerCenter = {0, 0};
    playerCenter.x = player->dest.x + player->dest.width / 2.0f;
    playerCenter.y = player->dest.y + player->dest.height / 2.0f;

    if (playerCenter.x <= GetScreenWidth()/2)
        camera->target.x = 512;
    else
        camera->target.x = player->dest.x + player->dest.width / 2.0f;
        
    if (playerCenter.y <= GetScreenHeight()/2)
        camera->target.y = 416;
    else
        camera->target.y = player->dest.y + player->dest.height / 2.0f;

    // Track object every frame.
    // camera->target = (xVector2)
    // {
    //     player->dest.x + player->dest.width / 2.0f,
    //     player->dest.y + player->dest.height / 2.0f
    // };
}

void xCameraDebugLines(xCamera2D *camera)
{
    DrawLine((int)camera->target.x, -GetScreenHeight()*10, (int)camera->target.x, GetScreenHeight()*10, YELLOW);
    DrawLine(-GetScreenWidth()*10, (int)camera->target.y, GetScreenWidth()*10, (int)camera->target.y, YELLOW);
}
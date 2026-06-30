#include "player.h"
#include "gameconfig.h"

static float deltaTime = 0.0f;
static const float interval = 0.15f;

static const int totalFrames = 6;
static const int frameWidth = 32;
static const int frameHeight = 32;

/** Player Object is made in main file,
 * here we simply define all funcitons and
 * possible opertaion on Player.
 */

void xInitPlayer(Player *player)
{
    player->texture = LoadTexture(PATH_PLAYER_SHEET);
    SetTextureFilter(player->texture, TEXTURE_FILTER_POINT);

    player->source = (Rectangle) {0, 0, frameWidth, frameHeight};
    player->dest = (Rectangle) {100, 100, frameWidth * 4, frameHeight * 4};

    player->speed = 3;
    
    player->state = playerIdle;
    player->direction = faceFront;
    player->flip = false;
}

void xUpdatePlayer(Player *player)
{
    xMovePlayer(player);
    xUpdatePlayerAnimation(player);
}

void xUnloadPlayer(Player *player)
{
    UnloadTexture(player->texture);
}

void xDrawPlayer(Player *player)
{
    if (player->flip)
    {
        player->source.width *= -1;
        DrawTexturePro(player->texture, player->source, player->dest, (Vector2) {0, 0}, 0.0f, WHITE);
    }
    else
    {
        DrawTexturePro(player->texture, player->source, player->dest, (Vector2) {0, 0}, 0.0f, WHITE);
    }
}

void xMovePlayer(Player *player)
{
    bool moving = false;

    if (IsKeyDown(KEY_W) && player->dest.y >= 0)
    {
        player->state = playerWalking;
        player->direction = faceBack;

        player->dest.y -= player->speed;
        moving = true;
    }

    if (IsKeyDown(KEY_S) && player->dest.y <= 832 - frameHeight * 4)
    {
        player->state = playerWalking;
        player->direction = faceFront;

        player->dest.y += player->speed;
        moving = true;
    }

    if (IsKeyDown(KEY_A) && player->dest.x >= 0)
    {
        player->state = playerWalking;
        player->direction = faceLeft;

        player->flip = true;
        player->dest.x -= player->speed;
        moving = true;
    }

    if (IsKeyDown(KEY_D) && player->dest.x <= 1024 - frameWidth * 4)
    {
        player->state = playerWalking;
        player->direction = faceRight;

        player->flip = false;
        player->dest.x += player->speed;
        moving = true;
    }

    if (!moving)
    {
        player->state = playerIdle;
    }
}

void xUpdatePlayerAnimation(Player *player)
{
    // ---------------- SELECT SPRITE ROW ----------------

    if (player->state == playerIdle)
    {
        switch (player->direction)
        {
        case faceFront:
            player->source.y = frameHeight * 0;
            break;

        case faceLeft:
        case faceRight:
            player->source.y = frameHeight * 1;
            break;

        case faceBack:
            player->source.y = frameHeight * 2;
            break;
        }
    }
    else if (player->state == playerWalking)
    {
        switch (player->direction)
        {
        case faceFront:
            player->source.y = frameHeight * 3;
            break;

        case faceLeft:
        case faceRight:
            player->source.y = frameHeight * 4;
            break;

        case faceBack:
            player->source.y = frameHeight * 5;
            break;
        }
    }

    // ---------------- ANIMATION TIMER ----------------

    deltaTime += GetFrameTime();

    if (deltaTime >= interval)
    {
        player->source.x += frameWidth;

        if (player->source.x >= frameWidth * totalFrames)
        {
            player->source.x = 0;
        }

        deltaTime -= interval;
    }

    player->source.width = frameWidth;
}
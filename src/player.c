#include "player.h"
#include "gameconfig.h"

#include "raymath.h"

static float deltaTime = 0.0f;
static const float interval = 0.10f;

static const int totalFrames = 6;
static const int frameWidth = 32;
static const int frameHeight = 32;

/** Player Object is made in main file,
 * here we simply define all funcitons and
 * possible opertaion on Player.
 */

void xInitPlayer(Player *player)
{
    player->spriteSheet = LoadTexture(PATH_PLAYER_SHEET);
    SetTextureFilter(player->spriteSheet, TEXTURE_FILTER_POINT);

    player->source = (Rectangle) {0, 0, frameWidth, frameHeight};
    player->dest = (Rectangle) {100, 100, frameWidth * 4, frameHeight * 4};

    player->speed = 3;
    
    player->state = PLAYER_IDLE;
    player->direction = PLAYER_FACE_FRONT;
    player->flip = false;
}

void xUpdatePlayer(Player *player)
{
    xMovePlayer(player);
    xUpdatePlayerAnimation(player);
}

void xUnloadPlayer(Player *player)
{
    UnloadTexture(player->spriteSheet);
}

void xDrawPlayer(Player *player)
{
    Rectangle drawSource = player->source;

    if (player->flip)
    {
        drawSource.x += drawSource.width;
        drawSource.width *= -1;
    }

    DrawTexturePro(player->spriteSheet, drawSource, player->dest, (Vector2) {0, 0}, 0.0f, WHITE);
}

void xMovePlayer(Player *player)
{
    int dx = 0;     // movement vector's x
    int dy = 0;     // movement vector's y

    bool moving = false;

    if (IsKeyDown(KEY_W) && player->dest.y >= 0)
    {
        player->state = PLAYER_WALKING;
        player->direction = PLAYER_FACE_BACK;

        dy--;
        moving = true;
    }

    if (IsKeyDown(KEY_S) && player->dest.y <= SCREEN_HEIGHT - frameHeight * 4)
    {
        player->state = PLAYER_WALKING;
        player->direction = PLAYER_FACE_FRONT;

        dy++;
        moving = true;
    }

    if (IsKeyDown(KEY_A) && player->dest.x >= 0)
    {
        player->state = PLAYER_WALKING;
        player->direction = PLAYER_FACE_LEFT;

        player->flip = true;
        
        dx--;
        moving = true;
    }

    if (IsKeyDown(KEY_D) && player->dest.x <= SCREEN_WIDTH - frameWidth * 4)
    {
        player->state = PLAYER_WALKING;
        player->direction = PLAYER_FACE_RIGHT;

        player->flip = false;
        
        dx++;
        moving = true;
    }

    if (!moving)
    {
        player->state = PLAYER_IDLE;

        dx = 0;     // reset dx
        dy = 0;     // reset dy
    }
    
    // Create a movement vector from player input.
    // Essentially copy values every frame (only 2 floats: x, y)
    Vector2 movement = {dx, dy};

    if (Vector2Length(movement) > 0)
    {
        // Normalize diagonal movement to maintain a constant speed.
        movement = Vector2Normalize(movement);

        player->dest.x += movement.x * player->speed;
        player->dest.y += movement.y * player->speed;
    }
}

void xUpdatePlayerAnimation(Player *player)
{
    // ---------------- SELECT SPRITE ROW ----------------

    if (player->state == PLAYER_IDLE)
    {
        // Select the correct animation row.
        switch (player->direction)
        {
        case PLAYER_FACE_FRONT:
            player->source.y = frameHeight * 0;
            break;

        case PLAYER_FACE_LEFT:
        case PLAYER_FACE_RIGHT:
            player->source.y = frameHeight * 1;
            break;

        case PLAYER_FACE_BACK:
            player->source.y = frameHeight * 2;
            break;
        }
    }

    else if (player->state == PLAYER_WALKING)
    {
        // Select the correct animation row.
        switch (player->direction)
        {
        case PLAYER_FACE_FRONT:
            player->source.y = frameHeight * 3;
            break;

        case PLAYER_FACE_LEFT:
        case PLAYER_FACE_RIGHT:
            player->source.y = frameHeight * 4;
            break;

        case PLAYER_FACE_BACK:
            player->source.y = frameHeight * 5;
            break;
        }
    }

    // ---------------- ANIMATION TIMER ----------------

    // Advance to the next animation frame.
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
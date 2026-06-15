#include "../include/raylib.h"

float deltaTime = 0.0f;
const float interval = 0.15f;

enum PLAYER_STATE
{
    playerIdle,
    playerWalking
};

enum PLAYER_DIRECTION
{
    faceFront,
    faceBack,
    faceLeft,
    faceRight
};

enum PLAYER_STATE playerState = playerIdle;
enum PLAYER_DIRECTION playerDirection = faceFront;

bool flipPlayer = false;

const int playerSpeed = 2;
const int frameWidth = 32;
const int frameHeight = 32;
const int totalFrames = 6;

void MovePlayer(float *x, float *y)
{
    bool moving = false;

    if (IsKeyDown(KEY_W) && *y >= 0)
    {
        playerState = playerWalking;
        playerDirection = faceBack;

        *y -= playerSpeed;
        moving = true;
    }

    if (IsKeyDown(KEY_S) && *y <= 800 - frameHeight * 4)
    {
        playerState = playerWalking;
        playerDirection = faceFront;

        *y += playerSpeed;
        moving = true;
    }

    if (IsKeyDown(KEY_A) && *x >= 0)
    {
        playerState = playerWalking;
        playerDirection = faceLeft;

        flipPlayer = true;
        *x -= playerSpeed;
        moving = true;
    }

    if (IsKeyDown(KEY_D) && *x <= 1000 - frameWidth * 4)
    {
        playerState = playerWalking;
        playerDirection = faceRight;

        flipPlayer = false;
        *x += playerSpeed;
        moving = true;
    }

    if (!moving)
    {
        playerState = playerIdle;
    }
}

void UpdatePlayerAnimation(Rectangle *source)
{
    // ---------------- SELECT SPRITE ROW ----------------

    if (playerState == playerIdle)
    {
        switch (playerDirection)
        {
        case faceFront:
            source->y = frameHeight * 0;
            break;

        case faceLeft:
        case faceRight:
            source->y = frameHeight * 1;
            break;

        case faceBack:
            source->y = frameHeight * 2;
            break;
        }
    }
    else if (playerState == playerWalking)
    {
        switch (playerDirection)
        {
        case faceFront:
            source->y = frameHeight * 3;
            break;

        case faceLeft:
        case faceRight:
            source->y = frameHeight * 4;
            break;

        case faceBack:
            source->y = frameHeight * 5;
            break;
        }
    }

    // ---------------- ANIMATION TIMER ----------------

    deltaTime += GetFrameTime();

    if (deltaTime >= interval)
    {
        source->x += frameWidth;

        if (source->x >= frameWidth * totalFrames)
        {
            source->x = 0;
        }

        deltaTime -= interval;
    }

    source->width = frameWidth;
}

int main(void)
{
    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 832;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Uprise");

    // Load player
    Texture2D sheet = LoadTexture("assets/player/player.png");
    SetTextureFilter(sheet, TEXTURE_FILTER_POINT);

    // Load map
    Texture2D map = LoadTexture("assets/maps/map1.png");
    SetTextureFilter(map, TEXTURE_FILTER_POINT);

    Rectangle mapSource = {0, 0, 1000, 800};

    // Source rectangle on sprite sheet
    Rectangle source = {0, 0, frameWidth, frameHeight};

    // Destination rectangle on screen
    Rectangle dest = {100, 100, frameWidth * 4, frameHeight * 4};

    Vector2 origin = {0, 0};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // ---------------- UPDATE ----------------

        MovePlayer(&dest.x, &dest.y);
        UpdatePlayerAnimation(&source);

        // Prepare sprite for rendering
        Rectangle drawSource = source;

        if (flipPlayer)
        {
            drawSource.x += frameWidth;
            drawSource.width = -frameWidth;
        }

        // ---------------- DRAW ----------------

        BeginDrawing();

            ClearBackground(GREEN);

            DrawTextureRec(map, mapSource, (Vector2){0, 0}, WHITE);

            DrawTexturePro(sheet, drawSource, dest, origin, 0.0f, WHITE);

            DrawCircle(GetMouseX(), GetMouseY(), 10, RED);

        EndDrawing();
    }

    UnloadTexture(sheet);
    UnloadTexture(map);

    CloseWindow();

    return 0;
}
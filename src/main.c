#include "../inlcude/raylib.h"

enum PLAYER_STATE
{
    playerIdleFront,
    playerIdleBack,
    playerWalkingBack,
    playerWalkingFront,
    playerWalkingLeft,
    playerWalkingRight    
};

enum PLAYER_STATE playerState = playerIdleFront;
int playerSpeed = 10;

void Move(float* x, float* y)
{
    if(IsKeyDown(KEY_W) && *y >= 0)
    {
        playerState = playerWalkingBack;
        *y -= playerSpeed;
    }
    if(IsKeyDown(KEY_S) && *y <= 800-32*4)
    {
        playerState = playerWalkingFront;
        *y += playerSpeed;
    }
    if(IsKeyDown(KEY_A) && *x >= 0)
    {
        playerState = playerWalkingLeft;
        *x -= playerSpeed;
    }
    if(IsKeyDown(KEY_D) && *x <= 1000-32*4)
    {
        playerState = playerWalkingRight;
        *x += playerSpeed;
    }

    // Player stays idleFront if no keys pressed
    if(!(IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D)))
    {
        playerState = playerIdleFront;
    }
}

void updatePlayerSprite(float* x, float* y)
{
    if(playerState == playerIdleFront)
    {
        *y = 0;
        if(*x >= 0)
            *x += 32;
        else if(*x == 32*6)
            *x = 0;
    }
    else if(playerState == playerWalkingFront)
    {
        *y = 32*3;
        if(*x >= 0)
            *x += 32;
        else if(*x == 32*6)
            *x = 0;
    }
    else if(playerState == playerWalkingBack)
    {
        *y = 32*5;
        if(*x >= 0)
            *x += 32;
        else if(*x == 32*6)
            *x = 0;
    }
    else if(playerState == playerWalkingLeft)
    {
        *y = 32*4;
        if(*x >= 0)
            *x += 32;
        else if(*x == 32*6)
            *x = 0;
    }
    else if(playerState == playerWalkingRight)
    {
        *y = 32*4;
        if(*x >= 0)
            *x += 32;
        else if(*x == 32*6)
            *x = 0;
    }

}

int main()
{
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 800;

    // Initialize Window (First Step)
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Uprise");

    Texture2D player;
    // Load Player
    Texture2D sheet = LoadTexture("assets/player/player.png");
    SetTextureFilter(sheet, TEXTURE_FILTER_POINT);

    // Load Map
    Texture2D map = LoadTexture("assets/maps/map1.png");
    SetTextureFilter(map, TEXTURE_FILTER_POINT);
    Rectangle mapSource = {0, 0, 1000, 800};

    Rectangle source = {0, 0, 32, 32};
    Rectangle dest = {100, 100, 32*4, 32*4};
    Vector2 origin = {0, 0};

    SetTargetFPS(30);

    // Game-Loop
    while(!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(GREEN);

        DrawTextureRec(map, mapSource, (Vector2){0, 0}, WHITE);

        // DrawText("Hello, Raylib!", 250, 250, 30, DARKBLUE);
        // DrawText("Press Esc to quit...", 250, 300, 20, GRAY);

        Move(&dest.x, &dest.y);

        updatePlayerSprite(&source.x, &source.y);

        DrawTexturePro(sheet, source, dest, origin, 0.0f, WHITE);

        DrawCircle(GetMouseX(), GetMouseY(), 10, RED);

        EndDrawing();
    }

    UnloadTexture(sheet); // Free GPU
    CloseWindow();

    return 0;
}
#include "raylib.h"

#include "gameconfig.h"
#include "player.h"

const Vector2 ZERO_POSITION = {0, 0};

Player player;


int main(void)
{
    xInitWindow();
    
    // Load map
    Texture2D map = LoadTexture(PATH_MAP);
    SetTextureFilter(map, TEXTURE_FILTER_POINT);

    Rectangle mapSource = {0, 0, 1024, 832};

    xInitPlayer(&player);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // ---------------- UPDATE ----------------

        xUpdatePlayer(&player);

        // ---------------- DRAW ----------------

        BeginDrawing();

            ClearBackground(GREEN);

            DrawTextureRec(map, mapSource, ZERO_POSITION, WHITE);

            xDrawPlayer(&player);

            DrawCircle(GetMouseX(), GetMouseY(), 10, RED);

        EndDrawing();
    }

    xUnloadPlayer(&player);
    UnloadTexture(map);

    CloseWindow();

    return 0;
}
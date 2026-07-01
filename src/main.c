#include "raylib.h"

#include "gameconfig.h"
#include "player.h"
#include "map.h"

Player player;
Map map;

int main(void)
{
    xInitWindow();

    xInitPlayer(&player);
    xInitMap(&map);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // ---------------- UPDATE ----------------

        xUpdatePlayer(&player);

        // ---------------- DRAW ----------------

        BeginDrawing();

            ClearBackground(GREEN);

            xDrawMap(&map);

            xDrawPlayer(&player);

            DrawCircle(GetMouseX(), GetMouseY(), 10, RED);

        EndDrawing();
    }

    xUnloadPlayer(&player);
    xUnloadMap(&map);

    CloseWindow();

    return 0;
}
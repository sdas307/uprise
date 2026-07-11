#include "raylib.h"
#include "config.h"
#include "player.h"
#include "world.h"
#include "render.h"
#include "animal.h"

Player player;
World world;
Animal animal;

int main(void)
{
    xInitWindow();

    xInitPlayer(&player);
    xInitWorld(&world);

    xLoadWorld(&world);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // ---------------- UPDATE ----------------

        xUpdatePlayer(&player, &world);

        // ---------------- DRAW ----------------

        BeginDrawing();

            ClearBackground(GRAY);

            xRenderScene(&world, &player, &animal);
            
            DrawCircle(GetMouseX(), GetMouseY(), 10, RED);

        EndDrawing();
    }

    xUnloadPlayer(&player);
    xUnloadWorld(&world);

    CloseWindow();

    return 0;
}
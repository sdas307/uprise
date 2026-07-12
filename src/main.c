#include "raylib.h"
#include "config.h"
#include "player.h"
#include "world.h"
#include "render.h"
#include "animal.h"
#include "base.h"

#include <stdio.h>

Player player;
World world;
AnimalManager manager;
BaseConfig config;

int main(void)
{
    xInitWindow();

    xInitPlayer(&player);
    xInitWorld(&world);

    xLoadWorld(&world, &manager);

    xBaseInit(&config);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // ---------------- UPDATE ----------------

        xUpdatePlayer(&player, &world);

        // ---------------- DRAW ----------------

        BeginDrawing();

            ClearBackground(GRAY);

            xRenderScene(&world, &player, &manager);
            
            DrawCircle(GetMouseX(), GetMouseY(), 10, RED);

        EndDrawing();
    }

    xUnloadPlayer(&player);
    xUnloadWorld(&world);

    CloseWindow();

    return 0;
}
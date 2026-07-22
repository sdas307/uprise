#include "raylib.h"
#include "config.h"
#include "player.h"
#include "world.h"
#include "render.h"
#include "animal.h"
#include <stdio.h>

Player player;
World world;
AnimalManager manager;

int main(void)
{
    xInitWindow();

    xInitPlayer(&player);

    printf("\n\nInit World!\n\n");
    xInitWorld(&world);
    printf("\n\nDone Init World!\n\n");

    printf("\n\nLoading World!\n\n");
    xLoadWorld(&world, &manager);
    printf("\n\nLoaded World!\n\n");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // ---------------- UPDATE ----------------

        xUpdatePlayer(&player, &world);
        
        for (int i = 0; i < manager.animalCount; i++)
        {
            xUpdateAnimal(&manager.animals[i]);
        }

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
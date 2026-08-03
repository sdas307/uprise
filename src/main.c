#include "raylib.h"
#include "config.h"
#include "camera.h"
#include "player.h"
#include "world.h"
#include "render.h"
#include "animal.h"
#include <stdio.h>

xCamera2D camera;
Player player;
World world;
AnimalManager manager;

int main(void)
{
    xInitWindow();

    xInitPlayer(&player);

    xInitCamera(&camera, &player.gameObject);

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

        xUpdateCamera(&camera, &player.gameObject);
        
        for (int i = 0; i < manager.animalCount; i++)
        {
            xUpdateAnimal(&manager.animals[i], &world);
        }

        // ---------------- DRAW ----------------

        BeginDrawing();

            ClearBackground(GRAY);

            BeginMode2D(camera);

                xRenderScene(&world, &player, &manager);
                // xCameraDebugLines(&camera);
                
            EndMode2D();

            DrawCircle(GetMouseX(), GetMouseY(), 10, RED);

        EndDrawing();
    }

    xUnloadPlayer(&player);
    xUnloadWorld(&world);

    CloseWindow();

    return 0;
}
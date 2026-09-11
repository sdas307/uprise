#include "raylib.h"
#include "config.h"
#include "camera.h"
#include "animation.h"
#include "player.h"
#include "world.h"
#include "render.h"
#include "animal.h"
#include <stdio.h>

bool showFPS = true;

int main(void)
{
    xGameCamera gameCamera;
    Player player;
    World world;
    AnimalManager manager;

    xInitWindow();

    xInitPlayer(&player);
    
    xInitCamera(&gameCamera, &player.gameObject);

    printf("\n\nInitializing World!\n\n");
    xInitWorld(&world);
    printf("\n\nDone Initializing World!\n\n");

    printf("\n\nLoading World!\n\n");
    xLoadWorld(&world, &manager);
    printf("\n\nDone Loading World!\n\n");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Only 1 delta time variable exists.
        float dt = GetFrameTime();

        // ---------------- UPDATE ----------------

        xUpdatePlayer(&player, &world, gameCamera.camera, dt);

        // player.c calls this when needed.
        //xUpdateInteraction(&player.target, &world, gameCamera.camera, player.gameObject.collider);

        xUpdateAnimation(&world, dt);

        xUpdateCamera(&gameCamera, &player.gameObject, dt);
        
        for (int i = 0; i < manager.animalCount; i++)
        {
            xUpdateAnimal(&manager.animals[i], &world, dt);
        }

        // ---------------- DRAW ----------------

        BeginDrawing();

            ClearBackground(GRAY);

            BeginMode2D(gameCamera.camera);

                xRenderScene(&world, &player, &manager);
                xRenderInteractionTarget(&player.target);
                // xCameraDebugLines(&camera);
                
            EndMode2D();

            DrawCircle(GetMouseX(), GetMouseY(), 10, RED);

            if (showFPS)
                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, WHITE);

        EndDrawing();
    }

    xUnloadPlayer(&player);
    xUnloadWorld(&world);
    // xUnloadAnimal(&manager);

    CloseWindow();

    return 0;
}
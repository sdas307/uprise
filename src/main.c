#include "raylib.h"
#include "config.h"
#include "player.h"
#include "world.h"
#include "render.h"
#include "animal.h"

Player player;
World world;
AnimalManager manager;

int main(void)
{
    xInitWindow();

    xInitPlayer(&player);
    xInitWorld(&world);

    xLoadWorld(&world, &manager);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // ---------------- UPDATE ----------------

        xUpdatePlayer(&player, &world);
        xUpdateAnimal(&manager.animals[0]);
        xUpdateAnimal(&manager.animals[1]);

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
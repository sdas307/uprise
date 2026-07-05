#include "raylib.h"
#include "config.h"
#include "player.h"
#include "map.h"

void xReadyMapWithObjects(Map *map);

Player player;
Map map;

int main(void)
{
    xInitWindow();

    xInitPlayer(&player);
    xInitMap(&map);

    xReadyMapWithObjects(&map);

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

void xReadyMapWithObjects(Map *map)
{
    xAddObject(
        map,
        (Rectangle){0, 0, 64, 64},            
        (Rectangle){400, 300, 64, 64}        
    );

    xAddObject(
        map,
        (Rectangle){0, 0, 64, 64},
        (Rectangle){400, 364, 64, 64}
    );

    xAddObject(
        map,
        (Rectangle){0, 0, 64, 64},
        (Rectangle){464, 364+64, 64, 64}
    );
}
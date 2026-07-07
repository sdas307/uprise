#include "raylib.h"
#include "map.h"
#include "config.h"
#include "world.h"

void xInitMap(Map *map)
{
    map->terrain.texture = LoadTexture(PATH_MAP);
    SetTextureFilter(map->terrain.texture, TEXTURE_FILTER_POINT);

    map->terrain.source = (xRectangle){0, 0, 1024, 832};
    map->terrain.dest = (xRectangle){0, 0, 1024, 832};

    map->spriteSheet = LoadTexture(PATH_SPRITE_SHEET);
    SetTextureFilter(map->spriteSheet, TEXTURE_FILTER_POINT);

    map->objectCount = 0;
}

void xDrawMap(Map *map)
{
    DrawTextureRec(map->terrain.texture, map->terrain.source, ZERO_POSITION, WHITE);

    for (int i=0; i<map->objectCount; i++)
    {
        xGameObject *object = &map->objects[i];

        if (!object->active)
            continue;

        DrawTexturePro(map->spriteSheet, object->source, object->dest, ZERO_POSITION, 0, WHITE);
        DrawRectangleLinesEx(map->objects[i].collider, 1.0f, RED);
    }
}

void xUnloadMap(Map *map)
{
    UnloadTexture(map->terrain.texture);
    UnloadTexture(map->spriteSheet);
}
#include "raylib.h"
#include "map.h"
#include "config.h"
#include "world.h"

void xInitMap(Map *map)
{
    map->terrain.texture = LoadTexture(PATH_MAP);
    SetTextureFilter(map->terrain.texture, TEXTURE_FILTER_POINT);

    map->terrain.source = (Rectangle){0, 0, 1024, 832};
    map->terrain.dest = (Rectangle){0, 0, 1024, 832};

    map->spriteSheet = LoadTexture(PATH_SPRITE_SHEET);
    SetTextureFilter(map->spriteSheet, TEXTURE_FILTER_POINT);

    // map->terrain.active = true;

    map->objectCount = 0;
}

void xAddObject(Map *map, xRectangle source, xRectangle dest, xRectangle collider)
{
    if (map->objectCount >= MAX_OBJECTS)
        return;

    xGameObject *object = &map->objects[map->objectCount++];

    object->source = source;
    object->dest = dest;

    object->collider = collider;

    // object->collider = (Rectangle)
    // {
    //     dest.x + 4,
    //     dest.y + 44,
    //     dest.width - 10,
    //     12,
    // };    

    object->active = true;
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
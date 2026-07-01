#include "raylib.h"
#include "map.h"
#include "gameconfig.h"

void xInitMap(Map *map)
{
    map->texture = LoadTexture(PATH_MAP);
    SetTextureFilter(map->texture, TEXTURE_FILTER_POINT);

    map->source = (Rectangle){0, 0, 1024, 832};
    map->dest = (Rectangle){0, 0, 1024, 832};
}

void xDrawMap(Map *map)
{
    DrawTextureRec(map->texture, map->source, ZERO_POSITION, WHITE);
}

void xUnloadMap(Map *map)
{
    UnloadTexture(map->texture);
}
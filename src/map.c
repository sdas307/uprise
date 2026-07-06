#include "raylib.h"
#include "map.h"
#include "config.h"

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

void xAddObject(Map *map, Rectangle source, Rectangle dest)
{
    if (map->objectCount >= MAX_OBJECTS)
        return;

    xGameObject *object = &map->objects[map->objectCount++];

    object->source = source;
    object->dest = dest;
    object->collider = (Rectangle)
    {
        dest.x + 4,
        dest.y + 44,
        dest.width - 10,
        12,
    };

    object->active = true;
}

void xLoadMap(Map *map)
{
    xAddObject(
        map,
        (Rectangle){0, 64 * 2, 64, 64},
        (Rectangle){464, 300, 64, 64}
    );

    xAddObject(
        map,
        (Rectangle){0, 64 * 2, 64, 64},
        (Rectangle){400, 364, 64, 64}
    );

    xAddObject(
        map,
        (Rectangle){0, 64 * 3, 64, 64},
        (Rectangle){464, 364+64, 64, 64}
    );

    xAddObject(
        map,
        (Rectangle){0, 64 * 3, 64, 64},
        (Rectangle){464+64, 364+64, 64, 64}
    );

    xAddStone(
        map, STONE_SMALL,
        (Rectangle){464+128, 428, 64, 64}
    );

    // ################# Collider breaks here? ##########################
    xAddTree(
        map, TREE_SMALL,
        (Rectangle) {600, 500, 64 * 2, 64 * 3}
    );
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
}

/* ---------- Map Objects ---------- */

void xAddStone(Map *map, StoneType type, Rectangle dest)
{
    Rectangle source;

    switch (type)
    {
        case STONE_SMALL:
            source = (Rectangle) {64 * 2, 64 * 3, 64, 64};
            break;
        
        case STONE_MEDIUM:
            source = (Rectangle) {64 * 1, 64 * 3, 64, 64};
            break;
        
        case STONE_LARGE:
            source = (Rectangle) {64 * 0, 64 * 3, 64, 64};
            break;
    }

    xAddObject(map, source, dest);
}

void xAddTree(Map *map, TreeStage stage, Rectangle dest)
{
    Rectangle source;

    switch (stage)
    {
        case TREE_STUMP:
            source = (Rectangle) {64 * 0, 64 * 8, 64, 64};
            break;
        
        case TREE_CUT:
            source = (Rectangle) {64 * 1, 64 * 2, 64, 64};
            break;
        
        case TREE_SMALL:
            source = (Rectangle) {64 * 5, 64 * 4, 64 * 2, 64 * 3};
            break;

        case TREE_LARGE:
            source = (Rectangle) {64 * 8, 64 * 1, 64 * 3, 64 * 4};
            break;
    }

    xAddObject(map, source, dest);
}
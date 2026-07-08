#include "xrender.h"
#include "config.h"

void xRenderTerrain(Map *map)
{
    DrawTexturePro(map->terrain.texture, map->terrain.source, map->terrain.dest, ZERO_POSITION, 0, WHITE);
}

void xRenderMapObjects(Map *map)
{
    // Draw map objects
    for (int i=0; i<map->objectCount; i++)
    {
        xGameObject *object = &map->objects[i];

        if (!object->active)
            continue;

        DrawTexturePro(map->spriteSheet, object->source, object->dest, ZERO_POSITION, 0, WHITE);
        DrawRectangleLinesEx(map->objects[i].collider, 1.0f, RED);
    }
}

void xRenderPlayer(Player *player)
{
    Rectangle drawSource = player->gameObject.source;

    if (player->flip)
    {
        drawSource.x += drawSource.width;
        drawSource.width *= -1;
    }

    DrawTexturePro(player->gameObject.texture, drawSource, player->gameObject.dest, (Vector2) {0, 0}, 0.0f, WHITE);
    DrawRectangleLinesEx(player->gameObject.collider, 1.0f, RED);
}
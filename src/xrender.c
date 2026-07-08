#include "xrender.h"
#include "config.h"

void xRenderScene(Map *map, Player *player)
{
    xGameObject *renderList[256];
    int renderCount = 0;

    xRenderTerrain(map);

    // Add map objects
    for (int i = 0; i < map->objectCount; i++)
    {
        renderList[renderCount++] = &map->objects[i];
    }

    // Add player
    renderList[renderCount++] = &player->gameObject;

    // Compute depths
    for (int i = 0; i < renderCount; i++)
    {
        renderList[i]->depth =
            renderList[i]->collider.y +
            renderList[i]->collider.height;
    }

    // Sort by depth
    xSortRenderOrder(renderList, renderCount);

    // Render
    for (int i = 0; i < renderCount; i++)
    {
        xRenderObject(renderList[i]);
    }
}

void xRenderObject(xGameObject *object)
{

    Rectangle drawSource = object->source;

    if (object->flip)
    {
        drawSource.x += drawSource.width;
        drawSource.width *= -1;
    }

    DrawTexturePro(object->texture, drawSource, object->dest, ZERO_POSITION, 0, WHITE);
    DrawRectangleLinesEx(object->collider, 1.0f, RED);
}

void xRenderTerrain(Map *map)
{
    DrawTexturePro(map->terrain.texture, map->terrain.source, map->terrain.dest, ZERO_POSITION, 0, WHITE);
}

void xRenderMapObjects(Map *map)
{
    // Draw map objects
    for (int i = 0; i < map->objectCount; i++)
    {
        xGameObject *object = &map->objects[i];

        if (!object->active)
            continue;

        xRenderObject(object);
    }
}

void xSortRenderOrder(xGameObject **renderList, int count)
{
    bool swapped = false;

    for (int i = 0; i < count - 1; i++)
    {
        swapped = false;

        for (int j = 0; j < count - i - 1; j++)
        {
            if (renderList[j]->depth > renderList[j + 1]->depth)
            {
                xGameObject *temp = renderList[j];
                renderList[j] = renderList[j + 1];
                renderList[j + 1] = temp;

                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}
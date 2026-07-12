#include "render.h"
#include "config.h"

#include <stdio.h>

/* ---------- Signatures ---------- */

#define MAX_RENDERABLES 256

/// Return the fade area for the object.
static xRectangle xGetFadeArea(xGameObject *object);

/// Render object with color tint or opactiy.
static void xRenderObject(xGameObject *object, xColor tint);

/// Sort the render queue (array) by increasing depth values.
static void xSortRenderOrder(xGameObject **renderList, int count);

/// Render map background (terrain).
static void xRenderTerrain(World *world);


/* ---------- Implementation ---------- */

void xRenderScene(World *world, Player *player, AnimalManager *manager)
{
    xGameObject *renderList[MAX_RENDERABLES];
    int renderCount = 0;

    xRenderTerrain(world);

    // Add world objects
    for (int i = 0; i < world->objectCount; i++)
    {
        renderList[renderCount++] = &world->objects[i];
        renderList[renderCount++] = &manager->animals[i].gameObject;
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
        xGameObject *object = renderList[i];

        bool isObjectPlayer = (object->type == OBJECT_PLAYER);
        bool isObjectAnimal = (object->type == OBJECT_ANIMAL);

        bool isPlayerBehindObject = (object->depth > player->gameObject.depth);

        xRectangle fadeArea = xGetFadeArea(object);

        bool overlapsPlayer = xCheckCollisionAABB(fadeArea, player->gameObject.collider);

        xColor tint = WHITE;

        if (!isObjectPlayer && !isObjectAnimal && isPlayerBehindObject && overlapsPlayer)
        {
            tint = Fade(WHITE, 0.5f);
        }

        xRenderObject(object, tint);
    }
}

static void xRenderTerrain(World *world)
{
    DrawTexturePro(world->terrain.texture, world->terrain.source, world->terrain.dest, ZERO_POSITION, 0, WHITE);
}

static void xSortRenderOrder(xGameObject **renderList, int count)
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

static void xRenderObject(xGameObject *object, xColor tint)
{
    xRectangle drawSource = object->source;

    if (object->flip)
    {
        drawSource.x += drawSource.width;
        drawSource.width *= -1;
    }

    DrawTexturePro(object->texture, drawSource, object->dest, ZERO_POSITION, 0.0f, tint);
    // DrawRectangleLinesEx(object->collider, 1.0f, RED);
    // DrawRectangleLinesEx(object->dest, 1.0f, RED);
}

static xRectangle xGetFadeArea(xGameObject *object)
{
    return (
        (xRectangle)
        {
            object->dest.x,
            object->dest.y,
            object->dest.width,
            object->dest.height
    });
}
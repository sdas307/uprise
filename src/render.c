#include "render.h"
#include "config.h"
#include "xEngine.h"

#include <stdio.h>

/* ---------- Signatures ---------- */

#define MAX_RENDERABLES 256

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

    // Add world objects.
    for (int i = 0; i < world->entityCount; i++)
    {
        renderList[renderCount++] = &world->entities[i].gameObject;
    }

    // Add animals.
    for (int i = 0; i < manager->animalCount; i++)
    {
        renderList[renderCount++] = &manager->animals[i].entity.gameObject;
    }

    // Add player
    renderList[renderCount++] = &player->entity.gameObject;

    // Sort by depth
    xSortRenderOrder(renderList, renderCount);

    // Render
    for (int i = 0; i < renderCount; i++)
    {
        Entity *entity = &world->entities[i];
        xGameObject *object = renderList[i];
        
        bool isObjectPlayer = (entity->type == PLAYER);
        bool isObjectAnimal = (entity->type == ANIMAL);

        bool fadeEffect = (object->fadeable);

        bool isPlayerBehindObject = (object->depth > player->entity.gameObject.depth);

        bool overlapsPlayer = xCheckCollisionAABB(object->fadeArea, player->entity.gameObject.collider);

        xColor tint = WHITE;

        if (!isObjectPlayer && isPlayerBehindObject && overlapsPlayer && fadeEffect)
        {
            tint = Fade(WHITE, 0.5f);
        }

        if (object->active)
            xRenderObject(object, tint);
    }
}

static void xRenderTerrain(World *world)
{
    DrawTexturePro(world->terrain.texture, world->terrain.source, world->terrain.dest, ZERO_POSITION, 0, WHITE);
}

void xRenderInteractionTarget(const InteractionTarget *target, const PlayerState state)
{
    if (!target->valid || state != PLAYER_ATTACK)
        return;

    // World Co-ordinates rectangle (from grid co-ordinates).
    xRectangle rectangle =
    {
        target->grid.x * WORLD_GRID_SIZE,
        target->grid.y * WORLD_GRID_SIZE,
        WORLD_GRID_SIZE,
        WORLD_GRID_SIZE,
    };

    DrawRectangleLinesEx(rectangle, 5.0f, WHITE);
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
        drawSource.width = -drawSource.width;
    }

    DrawTexturePro(object->texture, drawSource, object->dest, ZERO_POSITION, 0.0f, tint);
    // DrawRectangleLinesEx(object->collider, 1.0f, RED);
    // DrawRectangleLinesEx(object->dest, 1.0f, GREEN);
    // DrawRectangleLinesEx(object->fadeArea, 1.0f, BLACK);


    // DrawRectangleLinesEx(wanderZone, 1.0f, BLUE);
}
#include "interactions.h"

#include <stdlib.h>
#include <math.h>

/* ---------- Signatures ---------- */

/// Get mouse position in world co-ordinates.
static xVector2 getMouseWorldPosition(xCamera2D camera);

/// Convert world positions (pixels) to world grid positions.
static xVector2 getGridPosition(xVector2 position);

/// Return true if target cell is in player's range.
static bool isTargetInRange(xVector2 targetGrid, xVector2 playerGrid);


/* ---------- Implementation ---------- */


void xUpdateInteraction(InteractionTarget *target, World *world, xCamera2D camera, xVector2 playerPos)
{
    target->valid = false;
    target->entity = NULL;

    xVector2 mouseWorldPos = getMouseWorldPosition(camera);

    target->grid = getGridPosition(mouseWorldPos);

    // Convert player's position to grid co-ordinates.
    xVector2 playerGrid = getGridPosition(playerPos);

    // Only allow interaction with nearby cells.
    if (!isTargetInRange(target->grid, playerGrid))
    {
        return;
    }

    target->valid = true;

    // Find an entity occupying the target cell.
    for (int i=0; i < world->entityCount; i++)
    {
        Entity *entity = &world->entities[i];

        if (!entity->gameObject.active)
            continue;

        xRectangle collider = entity->gameObject.collider;

        int entityGridX = (int)floorf(collider.x / WORLD_GRID_SIZE);
        int entityGridY = (int)floorf(collider.y / WORLD_GRID_SIZE);

        if (entityGridX == target->grid.x && entityGridY == target->grid.y)
        {
            target->entity = entity;
            target->valid = true;

            // DrawRectangleLinesEx((xRectangle){target->grid.x, target->grid.y, 64, 64}, 2.0f, RED);

            return;
        }
    }
}

static xVector2 getMouseWorldPosition(xCamera2D camera)
{
    return GetScreenToWorld2D(GetMousePosition(), camera);
}

static xVector2 getGridPosition(xVector2 position)
{
    return (xVector2)
    {
        (int)floorf(position.x / WORLD_GRID_SIZE),
        (int)floorf(position.y / WORLD_GRID_SIZE)
    };
}

static bool isTargetInRange(xVector2 target, xVector2 player)
{
    int dx = abs(target.x - player.x);
    int dy = abs(target.y - player.y);

    // 1 cell away = 3x3 grid.

    return (dx <= PLAYER_TARGET_RANGE && dy <= PLAYER_TARGET_RANGE);
}
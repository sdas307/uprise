#include "interactions.h"
#include "entities.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* ---------- Signatures ---------- */

/// Get mouse position in world co-ordinates.
static xVector2 GetMouseWorldPosition(xCamera2D camera);

/// Convert world positions (pixels) to world grid positions.
static xVector2 GetGridPosition(xVector2 position);

/// Return true if target cell is in player's range.
static bool IsTargetInRange(xVector2 targetGrid, xVector2 playerGrid);

/// Make the change in the entity upon interaction.
static void Interact(InteractionTarget *target);


/* ---------- Implementation ---------- */

void xUpdateInteraction(InteractionTarget *target, World *world, xCamera2D camera, xRectangle playerCollider)
{
    // Reset target from previous frame.
    target->valid = false;
    target->entity = NULL;

    xVector2 mouseWorldPos = GetMouseWorldPosition(camera);

    target->grid = GetGridPosition(mouseWorldPos);

    // Convert player's position to grid co-ordinates.
    xVector2 playerColliderPos =
    {
        .x = playerCollider.x + playerCollider.width / 2,
        .y = playerCollider.y + playerCollider.height / 2
    };

    xVector2 playerGrid = GetGridPosition(playerColliderPos);

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

        int entityGridX = (int)floorf((collider.x + collider.width / 2) / WORLD_GRID_SIZE);
        int entityGridY = (int)floorf((collider.y + collider.height / 2) / WORLD_GRID_SIZE);

        if (entityGridX == target->grid.x && entityGridY == target->grid.y)
        {
            target->entity = entity;

            // Temporarily destroying objects via source = {0}.
            Interact(target);

            DrawRectangleLinesEx((xRectangle){target->grid.x, target->grid.y, 64, 64}, 6.0f, RED);

            return;
        }
    }
}

static xVector2 GetMouseWorldPosition(xCamera2D camera)
{
    return GetScreenToWorld2D(GetMousePosition(), camera);
}

static xVector2 GetGridPosition(xVector2 position)
{
    return (xVector2)
    {
        (int)floorf(position.x / WORLD_GRID_SIZE),
        (int)floorf(position.y / WORLD_GRID_SIZE)
    };
}

static bool IsTargetInRange(xVector2 target, xVector2 player)
{
    int dx = abs(target.x - player.x);
    int dy = abs(target.y - player.y);

    // 1 cell away = 3x3 grid.

    return (dx <= PLAYER_TARGET_RANGE && dy <= PLAYER_TARGET_RANGE);
}

static void Interact(InteractionTarget *target)
{
    if (!target->valid || !target->entity)
        return;
    
    Entity *entity = target->entity;

    switch (entity->interactionID)
    {
        case INTERACTION_DESTROY:
            entity->gameObject.active = false;
            break;

        case INTERACTION_CROP_HARVEST:
            break;

        case INTERACTION_FRUIT_HARVEST:
            break;

        case INTERACTION_FARMLAND_WATER:
            target->entity->id = ENTITY_FARMLAND_WET;
        break;

        case INTERACTION_TREE_CHOP:
            if (target->entity->id == ENTITY_TREE_OAK_LARGE)
            {
                target->entity->id = ENTITY_TREE_OAK_CUT;
            }

            if (target->entity->id == ENTITY_TREE_BIRCH_LARGE)
            {
                target->entity->id = ENTITY_TREE_BIRCH_CUT;
            }
        break;
    }
}
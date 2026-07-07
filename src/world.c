#include "world.h"

void xLoadMap(Map *map)
{
    xAddTree(map, TREE_CUT, (Rectangle){400, 364, 64, 64});

    xAddStone(map, STONE_LARGE, (Rectangle){464+64, 428, 64, 64});

    xAddStone(map, STONE_MEDIUM, (Rectangle){464+128, 428, 64, 64});

    xAddStone(map, STONE_SMALL, (Rectangle){464+192, 428, 64, 64});

    xAddTree(map, TREE_SMALL, (Rectangle){600, 500, 64 * 2, 64 * 2});
}

void xAddObject(Map *map, xRectangle source, xRectangle dest, xRectangle collider)
{
    if (map->objectCount >= MAX_OBJECTS)
        return;

    xGameObject *object = &map->objects[map->objectCount++];

    object->source = source;
    object->dest = dest;

    object->collider = collider;

    object->active = true;
}

void xAddStone(Map *map, StoneType type, xRectangle dest)
{
    Rectangle source;
    xRectangle collider;

    switch (type)
    {
        case STONE_SMALL:
            source = (Rectangle) {64 * 2, 64 * 3, 64, 64};

            collider = (Rectangle)
            {
                dest.x + 8,
                dest.y + 44,
                44,
                12,
            };
            break;
        
        case STONE_MEDIUM:
            source = (Rectangle) {64 * 1, 64 * 3, 64, 64};

            collider = (Rectangle)
            {
                dest.x + 12,
                dest.y + 44,
                45,
                12,
            };
            break;
        
        case STONE_LARGE:
            source = (Rectangle) {64 * 0, 64 * 3, 64, 64};

            collider = (Rectangle)
            {
                dest.x + 3,
                dest.y + 44,
                58,
                12,
            };
            break;
        
    }

    xAddObject(map, source, dest, collider);
}

void xAddTree(Map *map, TreeStage stage, xRectangle dest)
{
    xRectangle source;
    xRectangle collider;

    switch (stage)
    {
        case TREE_STUMP:
            source = (Rectangle) {64 * 0, 64 * 8, 64, 64};
            break;
        
        case TREE_CUT:
            source = (Rectangle) {64 * 0, 64 * 2, 64, 64};

            collider = (Rectangle)
            {
                dest.x,
                dest.y + 46,
                64,
                12,
            };
            break;
        
        case TREE_SMALL:
            source = (Rectangle) {64 * 5, 64 * 5, 64 * 2, 64 * 2};
            
            collider = (Rectangle)
            {
                dest.x + dest.width/2 - 15,
                dest.y + 98,
                20,
                12,
            };
            break;

        case TREE_LARGE:
            source = (Rectangle) {64 * 8, 64 * 1, 64 * 3, 64 * 4};
            break;
    }

    xAddObject(map, source, dest, collider);
}
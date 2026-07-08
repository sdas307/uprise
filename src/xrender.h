#ifndef X_RENDER_H
#define X_RENDER_H

#include "xEngine.h"
#include "player.h"
#include "map.h"

void xRenderScene(Map *map, Player *player);

void xRenderTerrain(Map *map);

void xRenderMapObjects(Map *map);

void xRenderObject(xGameObject *object);

void xSortRenderOrder(xGameObject **renderList, int count);

void xRenderPlayer(Player *player);

#endif